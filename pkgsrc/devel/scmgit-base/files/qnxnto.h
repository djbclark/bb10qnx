
#include <sys/procmsg.h>
#include <signal.h>
#include <stdint.h>
#include <process.h>

#ifndef SA_RESTART
#define SA_RESTART      0x0040

int sigaction_qnx(int, const struct sigaction *, struct sigaction *);
pid_t _fork(const unsigned, const uintptr_t);
	                

#define sigaction(a, b, c)	sigaction_qnx((a), (b), (c))
#define fork()			_fork(_FORK_ASPACE, 0)
#endif
