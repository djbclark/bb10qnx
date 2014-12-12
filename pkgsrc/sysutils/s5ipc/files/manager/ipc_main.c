/*
 * Resource manager to handle Sysv IPCs
 */
#include <stdio.h>
#include <sys/dispatch.h>
#include <sys/procmgr.h>

#include "shm_private.h"

static int shm_resid;

extern int shm_resinit(dispatch_t *dpp);

int main(int argc, char **argv)
{
	dispatch_t *dpp;
	int ch;
	int opt_daemon = 1;

	while ((ch = getopt(argc, argv, "f")) != -1) {
		switch(ch) {
		  case 'f':
			opt_daemon = 0;
			break;
		}
	}
	
	if ((dpp = dispatch_create()) == NULL) {
		perror("dispatch_create");
		return -1;
	}
	
	// shm resmgr
	if ((shm_resid = shm_resinit(dpp)) == -1) {
		return -1;
	}
	
	if (opt_daemon) {
		procmgr_daemon(0, PROCMGR_DAEMON_NOCLOSE | PROCMGR_DAEMON_NODEVNULL);
	}

	pause();
	
	return 0;
}
