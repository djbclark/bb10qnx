$NetBSD$

--- contrib/opvp/gdevopvp.c.orig	2012-02-08 08:48:49.000000000 +0000
+++ contrib/opvp/gdevopvp.c
@@ -25,7 +25,9 @@
 #include <unistd.h>
 #include <string.h>
 #include <locale.h>
+#ifndef __QNXNTO__
 #include <langinfo.h>
+#endif
 #include <dlfcn.h>
 #include <sys/types.h>
 #include <sys/stat.h>
