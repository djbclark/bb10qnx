#include <sys/platform.h>
/* Abracadabra! our time_t is now signed */
#undef __TIME_T
#define __TIME_T _Int32t
