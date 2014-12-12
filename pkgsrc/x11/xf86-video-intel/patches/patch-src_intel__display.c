$NetBSD$

--- src/intel_display.c.orig	2012-03-26 13:25:33.000000000 +0000
+++ src/intel_display.c
@@ -35,6 +35,9 @@
 #include <unistd.h>
 #include <errno.h>
 #include <poll.h>
+#ifdef __QNXNTO__
+#include <sys/select.h>
+#endif
 
 #include "xorgVersion.h"
 
