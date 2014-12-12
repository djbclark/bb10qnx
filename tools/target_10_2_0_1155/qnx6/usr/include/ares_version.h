
#ifndef ARES__VERSION_H
#define ARES__VERSION_H

/* This is the global package copyright */
#define ARES_COPYRIGHT "2004 - 2010 Daniel Stenberg, <daniel@haxx.se>."

#define ARES_VERSION_MAJOR 1
#define ARES_VERSION_MINOR 7
#define ARES_VERSION_PATCH 4
#define ARES_VERSION ((ARES_VERSION_MAJOR<<16)|\
                       (ARES_VERSION_MINOR<<8)|\
                       (ARES_VERSION_PATCH))
#define ARES_VERSION_STR "1.7.4"

#if (ARES_VERSION >= 0x010700)
#  define CARES_HAVE_ARES_LIBRARY_INIT 1
#  define CARES_HAVE_ARES_LIBRARY_CLEANUP 1
#else
#  undef CARES_HAVE_ARES_LIBRARY_INIT
#  undef CARES_HAVE_ARES_LIBRARY_CLEANUP
#endif

#ifdef __QNXNTO__
#if ARES_VERSION==0x010704
#define QNX_ARES_ADDRTTL 1
#endif
#endif
#endif

__SRCVERSION( "$URL$ $Rev$" )
