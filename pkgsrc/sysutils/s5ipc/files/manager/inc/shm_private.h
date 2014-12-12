#ifndef SHM_PRIVATE_H_
#define SHM_PRIVATE_H_

#include <unistd.h>
#include <devctl.h>
#include <sys/dispatch.h>
#include <sys/iomgr.h>

#include "sys/shm.h"

#define SHMSEG_FREE             0x0200
#define SHMSEG_ALLOCATED        0x0800

enum _shmmgr_subtypes {
	  _SHMMGR_GET,
	  _SHMMGR_ATTACH,
	  _SHMMGR_DETACH,
	  _SHMMGR_CTL
};

struct _shmmgr_get {
	struct  _io_msg             hdr;
	key_t                       key;
	size_t	                    size;
	int                         flag;
};

struct _shmmgr_get_reply {
	int                         shmid;
	key_t                       key;
};

typedef union {
	struct _shmmgr_get          i;
	struct _shmmgr_get_reply    o;
} shmmgr_get_t;

struct _shmmgr_attach {
	struct _io_msg              hdr;
	int                         shmid;
	int                         flag;
};

struct _shmmgr_attach_reply {
	size_t                      size;
};

typedef union {
	struct _shmmgr_attach       i;
	struct _shmmgr_attach_reply o;
} shmmgr_attach_t;

struct _shmmgr_detach {
	struct _io_msg              hdr;
	int                         shmid;
};

struct _shmmgr_detach_reply {
	size_t                      size;
};

typedef union {	
	struct _shmmgr_detach       i;
	struct _shmmgr_detach_reply o;
} shmmgr_detach_t;

struct _shmmgr_ctl {
	struct _io_msg              hdr;
	int                         shmid;
	int                         cmd;
	struct shmid_ds             buf;
};

typedef union {
	struct _shmmgr_ctl          i;
	struct _shmmgr_ctl          o;
} shmmgr_ctl_t;

#define PATH_SHMMGR             "/dev/ipc/shm/shmmgr"
#define PATH_SHM                "/dev/ipc/shm/"
#define _IOMGR_SHMMGR           (_IOMGR_PRIVATE_BASE + 'S')

// manager
extern int shmres_init(dispatch_t *dpp);
#endif /*SHM_PRIVATE_H_*/
