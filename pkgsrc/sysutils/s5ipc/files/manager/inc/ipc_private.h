#ifndef IPC_PRIVATE_H_
#define IPC_PRIVATE_H_

#include <sys/neutrino.h>
#include <sys/ipc.h>

extern int ipcperm(struct _client_info *info,  struct ipc_perm	*perm, int mode);
#endif
