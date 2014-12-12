#include "qnxnto.h"
#undef sigaction

#include <sys/neutrino.h>
#include <pthread.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>

static void *
restart_thread(void *arg)
{
	for (;;)
		pause();
}

static pthread_t
startit(void)
{
	sigset_t	fullset, oset;
	int		ret;
	pthread_t	tid;

	/* Start restart thread with all signals blocked */
	sigfillset(&fullset);
	pthread_sigmask(SIG_BLOCK, &fullset, &oset);

	if ((ret = pthread_create(&tid, NULL, restart_thread,
	    NULL)) != EOK) {
		tid = 0;
		errno = ret;
	}

	/* restore */
	pthread_sigmask(SIG_SETMASK, &oset, NULL);

	return tid;
}

int
sigaction_qnx(int sig, const struct sigaction *act, struct sigaction *oact)
{
	static pthread_t	restart_tid;
	sigset_t		nset, oset;
	struct sigaction	act_new;

	sigemptyset(&nset);
	sigaddset(&nset, sig);

	if (act->sa_flags & SA_RESTART) {
		if (restart_tid == 0 && (restart_tid = startit()) == 0) {
			return -1;
		}

		/* Block in calling thread */
		pthread_sigmask(SIG_BLOCK, &nset, NULL);

		/* Make sure unblocked in restart thread if not already */
		SignalProcmask_r(0, restart_tid, SIG_UNBLOCK, &nset, NULL);

		act_new = *act;
		act_new.sa_flags &= ~SA_RESTART;
		act = &act_new;
	}
	else if (restart_tid != 0) {
		/* Unblock in calling thread */
		pthread_sigmask(SIG_UNBLOCK, &nset, NULL);
		/* Block in restart thread */
		SignalProcmask_r(0, restart_tid, SIG_BLOCK, &nset, NULL);
	}
	return sigaction(sig, act, oact);
}
