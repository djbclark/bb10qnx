$NetBSD$

--- lib/system.c.orig	2012-06-28 19:14:36.000000000 +0000
+++ lib/system.c
@@ -40,6 +40,9 @@
 #  include <pwd.h>
 # endif
 #endif
+#ifdef __QNXNTO__
+#include <sys/select.h>
+#endif
 
 /* We need to disable gnulib's replacement wrappers to get native
    Windows interfaces. */
