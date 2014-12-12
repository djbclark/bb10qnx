$NetBSD$

--- glib/giounix.c.orig	2013-06-02 23:20:49.000000000 +0000
+++ glib/giounix.c
@@ -33,7 +33,9 @@
 
 #include "config.h"
 
+#ifndef __QNXNTO__
 #define _POSIX_SOURCE		/* for SSIZE_MAX */
+#endif
 
 #include <sys/types.h>
 #include <sys/stat.h>
