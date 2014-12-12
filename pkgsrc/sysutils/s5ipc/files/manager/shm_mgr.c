#include <errno.h>
#include <fcntl.h>
#include <malloc.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/dispatch.h>
#include <sys/iofunc.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "ipc_private.h"
#include "shm_private.h"

// resmgr stuff
static resmgr_connect_funcs_t  shm_connect;
static resmgr_io_funcs_t       shm_io;
static iofunc_attr_t           shm_ioattr;
static int                     shm_resid;

// shmid_ds pool
#define SHMID_ARRAY_GROW       16
static struct shmid_ds_pool {
	struct shmid_ds            shmds;
	key_t                      key;
} *shmid_array;
static unsigned shmid_array_total;
static pthread_mutex_t shmid_array_mutex = PTHREAD_MUTEX_INITIALIZER;

static void *shmres_handle(void *arg)
{
	dispatch_t *dpp = (dispatch_t *)arg;
	resmgr_context_t *ctp;
	
	if ((ctp = resmgr_context_alloc(dpp)) == NULL) {
		perror("resmgr_context_alloc");
		return NULL;
	}

	while (1) {
		if ((ctp = resmgr_block(ctp)) == NULL) {
			break;
		}
		resmgr_handler(ctp);
	}
	
	return NULL;
}

static int
msg_get(resmgr_context_t *ctp, shmmgr_get_t *msgget, struct _client_info *info)
{
	struct shmid_ds_pool *sd;
	int i, error, fd, spare;
	char buf[128];
	
	spare = -1;
	sd = NULL;
	_mutex_lock(&shmid_array_mutex);
	
	if (msgget->i.key != IPC_PRIVATE) {
		/* see if the key related to a shmid already */
		for (i = 0; i < shmid_array_total; i++) {
			sd = &shmid_array[i];
			if (sd->shmds.shm_perm.mode & SHMSEG_FREE) {
				if (spare == -1)
				  spare = i;
			  continue;
			}
			if (sd->key == msgget->i.key)
			  break;
		}
		if (i == shmid_array_total) {
			sd = NULL;
		}
		
		if (sd != NULL) {
			/* if the key already exists */
			if ((error = ipcperm(info, &sd->shmds.shm_perm, msgget->i.flag & S_IPERMS)) != 0)
			{
				_mutex_unlock(&shmid_array_mutex);
				return error;
			}
			if (msgget->i.size && msgget->i.size > sd->shmds.shm_segsz) {
				_mutex_unlock(&shmid_array_mutex);
				return EINVAL;
			}
			if ((msgget->i.flag & (IPC_CREAT | IPC_EXCL)) == (IPC_CREAT | IPC_EXCL)) {
				_mutex_unlock(&shmid_array_mutex);
				return EEXIST;
			}
			msgget->o.key = msgget->i.key;
			msgget->o.shmid = i;
			_mutex_unlock(&shmid_array_mutex);
			MsgReply(ctp->rcvid, EOK, &msgget->o, sizeof(msgget->o));
			return _RESMGR_NOREPLY;				
		} else {
			// no sd associated with the key, we need an IPC_CREAT
			if ((msgget->i.flag & IPC_CREAT) == 0) {
				_mutex_unlock(&shmid_array_mutex);
				return ENOENT;
			}
			
		}
	}
		
	/* find a spare sd (we still have the mutex) */
	if (spare == -1) {
		for (i = 0; i < shmid_array_total; i++) {
			sd = &shmid_array[i];
			if (sd->shmds.shm_perm.mode & SHMSEG_FREE) {
				spare = i;
				break;
			}
		}
		if (i == shmid_array_total) {
			sd = NULL;
	
			sd = realloc(shmid_array, (shmid_array_total + SHMID_ARRAY_GROW) * sizeof(*sd));
			if (sd == NULL) {
				_mutex_unlock(&shmid_array_mutex);
				return errno;
			}
			for (i = shmid_array_total; i < shmid_array_total + SHMID_ARRAY_GROW; i++) {
				sd[i].shmds.shm_perm.mode |= SHMSEG_FREE;
			}
			i = shmid_array_total;
			shmid_array = sd;
			shmid_array_total += SHMID_ARRAY_GROW;
		}		
	} else {
		i = spare;
	}
	sd = &shmid_array[i];
	memset(sd, 0, sizeof(*sd));
	sd->shmds.shm_perm.mode = (msgget->i.flag & S_IPERMS) | SHMSEG_ALLOCATED;
	_mutex_unlock(&shmid_array_mutex);

	
	snprintf(buf, sizeof(buf), "%s/%d", PATH_SHM, i);
#if 0
	if ((fd = shm_open(buf, O_CREAT, (msgget->i.flag & S_IPERMS))) == -1 ||
		ftruncate(fd, msgget->i.size) == -1 ) 
	{
		goto fail;
	}
#else
	if ((fd = shm_open(buf, O_CREAT | O_RDWR, (msgget->i.flag & S_IPERMS))) == -1) {
		goto fail;
	}
	if (fchown(fd, info->cred.euid, info->cred.egid) == -1 ||
	    ftruncate(fd, msgget->i.size) == -1 ) {
		close(fd);
		shm_unlink(buf);
		goto fail;
	}
#endif
	close(fd);

	/* set up the sd */
	sd->shmds.shm_perm.cuid = info->cred.euid;
	sd->shmds.shm_perm.cgid = info->cred.egid;
	sd->shmds.shm_perm.uid  = info->cred.ruid;
	sd->shmds.shm_perm.gid  = info->cred.rgid;
	sd->shmds.shm_segsz     = msgget->i.size;
	sd->shmds.shm_cpid      = info->pid;
	sd->shmds.shm_ctime     = time(NULL);
	sd->key                 = msgget->i.key;
	
	/* reply to let client know the shmid */
	msgget->o.key     = msgget->i.key;
	msgget->o.shmid   = i;
	MsgReply(ctp->rcvid, EOK, &msgget->o, sizeof(msgget->o));
	return _RESMGR_NOREPLY;
	
fail:
	_mutex_lock(&shmid_array_mutex);
	sd->shmds.shm_perm.mode = SHMSEG_FREE;
	_mutex_unlock(&shmid_array_mutex);
	return errno;
}

static int
shm_msg(resmgr_context_t *ctp, io_msg_t *pmsg, RESMGR_OCB_T *ocb)
{
	union {
		io_msg_t        hdr;
		shmmgr_get_t    get;
		shmmgr_attach_t attach;
		shmmgr_detach_t detach;
		shmmgr_ctl_t    ctl;
	} *msg = (void *)pmsg;
	struct shmid_ds_pool *sd;
	struct _client_info  info;
	char buf[128];
	int status;
	
	if (msg->hdr.i.mgrid != _IOMGR_SHMMGR) {
		return _RESMGR_DEFAULT;
	}
	
	// we will always need the client info
	if ((status = ConnectClientInfo_r(ctp->info.scoid, &info, NGROUPS_MAX)) != EOK) {
		return status;
	}
	
	switch (msg->hdr.i.subtype) {
	case _SHMMGR_GET:
		return msg_get(ctp, &msg->get, &info);
		
	case _SHMMGR_ATTACH:
	case _SHMMGR_DETACH:
		if (msg->attach.i.shmid < 0 || msg->attach.i.shmid >= shmid_array_total) {
			return EINVAL;
		}
		_mutex_lock(&shmid_array_mutex);
		sd = &shmid_array[msg->attach.i.shmid];
		if (sd->shmds.shm_perm.mode & SHMSEG_FREE) {
			_mutex_unlock(&shmid_array_mutex);
			return EINVAL;
		}
		if ((status = ipcperm(&info, &sd->shmds.shm_perm, 
		    (msg->attach.i.flag & SHM_RDONLY) ? IPC_R : IPC_R | IPC_W)) != 0) {
			_mutex_unlock(&shmid_array_mutex);
			return status;
		}
		
		sd->shmds.shm_lpid = info.pid;
		sd->shmds.shm_atime = time(NULL);

		if (msg->hdr.i.subtype == _SHMMGR_ATTACH)
			sd->shmds.shm_nattch++;
		else
			sd->shmds.shm_nattch--;
		
		msg->attach.o.size = sd->shmds.shm_segsz;
		_mutex_unlock(&shmid_array_mutex);
		MsgReply(ctp->rcvid, EOK, &msg->attach.o, sizeof(msg->attach.o));
		break;

	case _SHMMGR_CTL:
		if (msg->ctl.i.shmid < 0 || msg->ctl.i.shmid >= shmid_array_total) {
			return EINVAL;
		}
		_mutex_lock(&shmid_array_mutex);
		sd = &shmid_array[msg->ctl.i.shmid];
		if (sd->shmds.shm_perm.mode & SHMSEG_FREE) {
			_mutex_unlock(&shmid_array_mutex);
			return EINVAL;
		}
		
		switch(msg->ctl.i.cmd) {
		  case IPC_STAT:
			if ((status = ipcperm(&info, &sd->shmds.shm_perm, IPC_R)) != 0) {
				_mutex_unlock(&shmid_array_mutex);
				return status;
			}
			memcpy(&msg->ctl.i.buf, &sd->shmds, sizeof(sd->shmds));
			break;
			
		  case IPC_SET:
			if ((status = ipcperm(&info, &sd->shmds.shm_perm, IPC_M)) != 0) {
				_mutex_unlock(&shmid_array_mutex);
				return status;
			}
			sd->shmds.shm_perm.uid = msg->ctl.i.buf.shm_perm.uid;
			sd->shmds.shm_perm.gid = msg->ctl.i.buf.shm_perm.gid;
			sd->shmds.shm_perm.mode = (msg->ctl.i.buf.shm_perm.mode & S_IPERMS) |
			  (sd->shmds.shm_perm.mode & ~S_IPERMS);
			sd->shmds.shm_ctime = time(NULL);
			break;

		  case IPC_RMID:
			if ((status = ipcperm(&info, &sd->shmds.shm_perm, IPC_M)) != 0) {
				_mutex_unlock(&shmid_array_mutex);
				return status;
			}
			snprintf(buf, sizeof(buf), "%s/%d", PATH_SHM, msg->ctl.i.shmid);
			shm_unlink(buf);
			sd->shmds.shm_perm.mode = SHMSEG_FREE;
			break;
		}
		_mutex_unlock(&shmid_array_mutex);
		MsgReply(ctp->rcvid, EOK, &msg->ctl.o, sizeof(msg->ctl.o));
	}
		
	return _RESMGR_NOREPLY;
}

int shm_resinit(dispatch_t *dpp)
{
	int ret;
	
	/* shmget() doesn't talk about umask but shm_open() does. */
	umask(0);

	iofunc_func_init(_RESMGR_CONNECT_NFUNCS, &shm_connect,
	    _RESMGR_IO_NFUNCS, &shm_io);
	shm_io.msg = shm_msg;
    
	iofunc_attr_init(&shm_ioattr, 0666, 0, 0);
	shm_resid = resmgr_attach(dpp, 0, PATH_SHMMGR, _FTYPE_ANY, 0,
	    &shm_connect, &shm_io, &shm_ioattr);
	if (shm_resid == -1) {
		return -1;
	}
    
	if ((ret = pthread_create(NULL, NULL, shmres_handle, dpp)) != EOK) {
		errno = ret;
		resmgr_detach(dpp, shm_resid, _RESMGR_DETACH_ALL);
		return -1;
	}
	
	return 0;
}
