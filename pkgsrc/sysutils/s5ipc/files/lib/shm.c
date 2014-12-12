/*
 * shm.c -- Sysv Shm implementation
 */
#include <errno.h>
#include <fcntl.h>
#include <malloc.h>
#include <pthread.h>
#include <stdio.h>
#include <share.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/neutrino.h>
#include <sys/slog.h>
#include <sys/slogcodes.h>

#include <sys/shm.h>
#include "shm_private.h"

#define SHMFD_ARRAY_INC          16

static pthread_mutex_t           shmfd_mutex = PTHREAD_MUTEX_INITIALIZER;
static unsigned                  shmfd_array_total;
static struct _shm_cache {
	int    shmid;
	void  *shmaddr;
} *shmfd_array;

static volatile int shmmgr_coid = -1;

static int
_shmfd_store(int shmfd, int shmid, void *shmaddr)
{
	int new_total, i;
	struct _shm_cache *sc, *new_array;
	
	_mutex_lock(&shmfd_mutex);
	if (shmfd < shmfd_array_total) {
		sc = &shmfd_array[shmfd];
	} else {
		new_total = shmfd_array_total + SHMFD_ARRAY_INC;
		if ((new_array = realloc(shmfd_array,
		    new_total * sizeof(struct _shm_cache))) == NULL) {
			return -1;
		}
		for (i = 0; i < SHMFD_ARRAY_INC; i++) {
			new_array[i].shmid = -1;
		}
		shmfd_array = new_array;
		shmfd_array_total = new_total;
		sc = &shmfd_array[shmfd];
	}
	sc->shmid = shmid;
	sc->shmaddr = shmaddr;
	_mutex_unlock(&shmfd_mutex);
	
	return 0;
}

static int
_shmfd_find(const void *addr, struct _shm_cache *sc, int remove)
{
	int i;
	
	_mutex_lock(&shmfd_mutex);
	for (i = 0; i < shmfd_array_total; i++) {
		if (shmfd_array[i].shmid != -1 &&
		    shmfd_array[i].shmaddr == addr) {
			break;
		}
	}	
	if (i == shmfd_array_total) {
		_mutex_unlock(&shmfd_mutex);
		errno = EINVAL;
		return -1;
	}
	if (sc != NULL)
		*sc = shmfd_array[i];
	if (remove)
		shmfd_array[i].shmid = -1;
	_mutex_unlock(&shmfd_mutex);
	
	return i;
}

static int
_shm_send(void *smsg, int ssize, void *rmsg, int rsize)
{
	int status = -1;
	int coid = shmmgr_coid;

	if (coid == -1 ||
	    ((status = MsgSend(coid, smsg, ssize, rmsg, rsize)) == -1 &&
	    (errno == EBADF || errno == ENOSYS))) {
		if (coid >= 0) {
			shmmgr_coid = -1;
			close(coid);
		}
		
		// connect
		coid = _connect(_NTO_SIDE_CHANNEL, PATH_SHMMGR, 0, O_RDWR,
		    SH_DENYNO, _IO_CONNECT_OPEN, 0, _IO_FLAG_RD | _IO_FLAG_WR,
		    0, 0, 0, 0, 0, 0, 0);

		if (coid == -1) {
			errno = ENOTSUP;
		} else {
			status = MsgSend(coid, smsg, ssize, rmsg, rsize);
			if (status == -1) {
				close(coid);
			} else {
				if (_smp_cmpxchg(
				    (volatile unsigned *)&shmmgr_coid, -1,
				    coid) != -1) {
					close(coid);
				}
			}
		}
	}
	
	return status;
}

int
shmget(key_t key, size_t size, int shmflag)
{
	shmmgr_get_t msg;

	msg.i.hdr.type = _IO_MSG;
	msg.i.hdr.combine_len = sizeof msg.i;
	msg.i.hdr.mgrid = _IOMGR_SHMMGR;
	msg.i.hdr.subtype = _SHMMGR_GET;
	msg.i.key = key;
	msg.i.size = size;
	msg.i.flag = shmflag;

	if (_shm_send(&msg, sizeof msg.i, &msg, sizeof msg.o) == -1) {
		return -1;
	}
	/*
	 * Added this for debugging firefox memory corruption issue
	 * and it reliably makes it dissapear.  Leaving for now...
	 */
	slogf(_SLOG_SETCODE(_SLOGC_TEST, 0), _SLOG_ERROR, "shmget: size: %u pid: %d",  size, getpid());
	
	return msg.o.shmid;
}

void *
shmat(int shmid, const void *shmaddr, int shmflag)
{
	shmmgr_attach_t msg;
	shmmgr_detach_t dmsg;
	int shmfd, proto, flags;
	char buf[32];
	void *addr;

	/* message */
	msg.i.hdr.type = _IO_MSG;
	msg.i.hdr.combine_len = sizeof msg.i;
	msg.i.hdr.mgrid = _IOMGR_SHMMGR;
	msg.i.hdr.subtype = _SHMMGR_ATTACH;
	msg.i.shmid = shmid;
	msg.i.flag = shmflag;
	
	if (_shm_send(&msg, sizeof msg.i, &msg, sizeof msg.o) == -1) {
		return (void *)-1;
	}
		
	snprintf(buf, sizeof(buf), "/dev/ipc/shm/%d", shmid);
	if ((shmfd = shm_open(buf, (shmflag & SHM_RDONLY) ? O_RDONLY : O_RDWR, 0)) == -1) {
		return (void *)-1;
	}
	
	/* make sure params make sense */
	proto = PROT_READ;
	if ((shmflag & SHM_RDONLY) == 0) {
		proto |= PROT_WRITE;
	}
	
	flags = MAP_SHARED;
	if (shmaddr != 0) {
		flags |= MAP_FIXED;
		if (shmflag & SHM_RND) {
			shmaddr = (void *)((uintptr_t)shmaddr & ~(SHMLBA - 1));
		} else if (((unsigned)shmaddr & (SHMLBA-1)) == 0) {
			errno = EINVAL;
			return (void *)-1;
		}
	}
	
	if ((addr = mmap((void *)shmaddr, msg.o.size, proto, flags, shmfd, 0)) == MAP_FAILED) {
		close(shmfd);
		return (void *)-1;
	}

	if (_shmfd_store(shmfd, shmid, addr) == -1) {
		munmap(addr, msg.o.size);
		close(shmfd);
		/* sent a detach message to let manager know */
		dmsg.i.hdr.type = _IO_MSG;
		dmsg.i.hdr.combine_len = sizeof msg.i;
		dmsg.i.hdr.mgrid = _IOMGR_SHMMGR;
		dmsg.i.hdr.subtype = _SHMMGR_DETACH;
		dmsg.i.shmid = shmid;
		_shm_send(&dmsg, sizeof dmsg.i, 0, 0);
		return (void *)-1;
	}

	return addr;
}

int
shmdt(const void *addr) 
{
	shmmgr_detach_t msg;
	struct _shm_cache sc;
	int shmfd;

	if ((shmfd = _shmfd_find(addr, &sc, 1)) == -1) {
		errno = EINVAL;
		return -1;
	}
	
	msg.i.hdr.type = _IO_MSG;
	msg.i.hdr.combine_len = sizeof msg.i;
	msg.i.hdr.mgrid = _IOMGR_SHMMGR;
	msg.i.hdr.subtype = _SHMMGR_DETACH;
	msg.i.shmid = sc.shmid;
	if (_shm_send(&msg.i, sizeof msg.i, &msg.o, sizeof msg.o) == -1) {
		return -1;
	}

	munmap((void *)addr, msg.o.size);
	close(shmfd);
	return 0;
}

int
shmctl(int shmid, int cmd, struct shmid_ds *buf)
{
	shmmgr_ctl_t msg;
	int status;
	
	msg.i.hdr.type = _IO_MSG;
	msg.i.hdr.combine_len = sizeof msg.i;
	msg.i.hdr.mgrid = _IOMGR_SHMMGR;
	msg.i.hdr.subtype = _SHMMGR_CTL;
	msg.i.shmid = shmid;
	msg.i.cmd = cmd;
	
	switch (cmd) {
	case IPC_STAT:
		if ((status = _shm_send(&msg.i, sizeof msg.i, &msg.o, sizeof msg.o)) != -1) {
			*buf = msg.o.buf;
		}
		break;
		
	case IPC_SET:
		msg.i.buf = *buf;
		status = _shm_send(&msg.i, sizeof msg.i, &msg.o, sizeof msg.o);
		break;
		
	case IPC_RMID:
	case SHM_LOCK:
	case SHM_UNLOCK:
		status = _shm_send(&msg.i, sizeof msg.i, &msg.o, sizeof msg.o);
		break;
		
	default:
		errno = EINVAL;
		status = -1;
		break;
	}
	
	return status;
}
