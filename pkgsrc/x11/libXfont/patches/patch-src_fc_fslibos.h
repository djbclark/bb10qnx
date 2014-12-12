$NetBSD$

--- src/fc/fslibos.h.orig	2011-09-17 05:20:36.000000000 +0000
+++ src/fc/fslibos.h
@@ -62,7 +62,7 @@ from The Open Group.
 # endif
 #endif
 #ifndef OPEN_MAX
-#if defined(SVR4)
+#if defined(SVR4) || defined(__QNXNTO__)
 #define OPEN_MAX 256
 #else
 #include <sys/param.h>
