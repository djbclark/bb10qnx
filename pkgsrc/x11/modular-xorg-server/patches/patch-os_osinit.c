$NetBSD$

--- os/osinit.c.orig	2012-05-17 17:09:04.000000000 +0000
+++ os/osinit.c
@@ -61,6 +61,9 @@ SOFTWARE.
 #ifdef HAVE_BACKTRACE
 #include <execinfo.h>
 #endif
+#ifdef __QNXNTO__
+#include <unix.h>
+#endif
 
 #include "misc.h"
 
