#include <errno.h>
#include <sys/ipc.h>
#include <sys/neutrino.h>
#include <sys/stat.h>

static int _ismember(struct _client_info *info, gid_t gid)
{
	int n;
	
	for (n = 0; n < info->cred.ngroups; n++) {
		if (info->cred.grouplist[n] == gid)
		  return 0;
	}
	return EACCES;
}

int ipcperm(struct _client_info *info,  struct ipc_perm	*perm, int mode)
{
	mode_t mask;
	
	if (mode == IPC_M) {
		if (info->cred.euid == perm->uid ||
			info->cred.euid == perm->cuid)
		  return 0;
		return EPERM;
	}
	
	mask = 0;
	
	if (info->cred.euid == perm->uid || info->cred.euid == perm->cuid) {
		if (mode & IPC_R)
		  mask |= S_IRUSR;
		if (mode & IPC_W)
		  mask |= S_IWUSR;
		return ((perm->mode & mask) == mask ? 0 : EACCES);
	}


	if (info->cred.egid == perm->gid  || _ismember(info, perm->gid) ||
		info->cred.egid == perm->cgid || _ismember(info, perm->cgid))
	{
		if (mode & IPC_R)
		  mask |= S_IRGRP;
		if (mode & IPC_W)
		  mask |= S_IWGRP;
		return ((perm->mode & mask) == mask ? 0 : EACCES);
	}
	
	if (mode & IPC_R)
	  mask |= S_IROTH;
	if (mode & IPC_W)
	  mask |= S_IWOTH;
	return ((perm->mode & mask) == mask ? 0 : EACCES);
}
