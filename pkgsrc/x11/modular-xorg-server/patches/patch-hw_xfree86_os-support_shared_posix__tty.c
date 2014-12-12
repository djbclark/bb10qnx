$NetBSD$

--- hw/xfree86/os-support/shared/posix_tty.c.orig	2012-05-17 17:09:03.000000000 +0000
+++ hw/xfree86/os-support/shared/posix_tty.c
@@ -55,6 +55,9 @@
 #ifdef HAVE_XORG_CONFIG_H
 #include <xorg-config.h>
 #endif
+#ifdef __QNXNTO__
+#include <termios.h>
+#endif
 
 #include <X11/X.h>
 #include "xf86.h"
