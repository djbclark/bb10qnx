$NetBSD$

--- hw/xfree86/common/xf86cmap.c.orig	2012-05-17 17:09:03.000000000 +0000
+++ hw/xfree86/common/xf86cmap.c
@@ -29,7 +29,7 @@
 #include <xorg-config.h>
 #endif
 
-#if defined(_XOPEN_SOURCE) || defined(sun) && defined(__SVR4)
+#if defined(_XOPEN_SOURCE) || defined(sun) && defined(__SVR4) || defined(__QNXNTO__)
 #include <math.h>
 #else
 #define _XOPEN_SOURCE           /* to get prototype for pow on some systems */
