$NetBSD$

--- nsprpub/pr/include/md/_nto.h.orig	2013-06-18 11:01:38.000000000 +0000
+++ nsprpub/pr/include/md/_nto.h
@@ -24,9 +24,13 @@
 #define	HAVE_WEAK_IO_SYMBOLS
 #endif
 
-#undef  _PR_POLL_AVAILABLE
-#undef  _PR_USE_POLL
+#define _PR_POLL_AVAILABLE
+#define _PR_USE_POLL
 #define _PR_HAVE_SOCKADDR_LEN
+#define _PR_HAVE_GETADDRINFO
+#define _PR_INET6
+#define _PR_HAVE_INET_NTOP
+#define _PR_HAVE_GETHOSTBYNAME2
 #undef  HAVE_BSD_FLOCK
 #define HAVE_FCNTL_FILE_LOCKING
 #define _PR_NO_LARGE_FILES
@@ -34,8 +38,6 @@
 #define PR_HAVE_POSIX_NAMED_SHARED_MEMORY
 #define _PR_HAVE_POSIX_SEMAPHORES
 
-#undef FD_SETSIZE
-#define FD_SETSIZE	4096
 #include <sys/time.h>
 #include <sys/types.h>
 #include <sys/select.h>
@@ -182,7 +184,13 @@ struct _MDCPU {
 ** unwrapped version.
 */
 #define _MD_SELECT		select
+#if defined(_PR_POLL_AVAILABLE)
+#include <poll.h>
+#define _MD_POLL poll
+#endif
 
+#ifndef SA_RESTART
 #define SA_RESTART 0
+#endif
 
 #endif /* nspr_nto_defs_h___ */
