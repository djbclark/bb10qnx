$NetBSD$

--- hw/xfree86/common/xf86Events.c.orig	2012-05-17 17:09:03.000000000 +0000
+++ hw/xfree86/common/xf86Events.c
@@ -83,6 +83,9 @@
 #include <X11/extensions/dpmsconst.h>
 #include "dpmsproc.h"
 #endif
+#ifdef __QNXNTO__
+#include <errno.h>
+#endif
 
 /*
  * This is a toggling variable:
