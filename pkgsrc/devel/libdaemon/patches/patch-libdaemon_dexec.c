$NetBSD: patch-libdaemon_dexec.c,v 1.1 2012/12/27 17:01:23 bsiegert Exp $

MirBSD does not have ECANCELED. EINTR is not really the right return value.
IMHO, it should return with exit status set to 127 instead.

--- libdaemon/dexec.c.orig	2009-04-20 00:58:07.000000000 +0000
+++ libdaemon/dexec.c
@@ -35,6 +35,9 @@
 #include <stdio.h>
 #include <stdarg.h>
 #include <assert.h>
+#ifdef __QNXNTO__
+#include <sys/select.h>
+#endif
 
 #include "dlog.h"
 #include "dsignal.h"
@@ -203,7 +206,11 @@ int daemon_execv(const char *dir, int *r
             return -1;
         } else {
             if (!WIFEXITED(r)) {
+#ifdef ECANCELED
                 errno = ECANCELED;
+#else
+                errno = EINTR; /* The child was terminated by a signal. */
+#endif
                 return -1;
             }
 
