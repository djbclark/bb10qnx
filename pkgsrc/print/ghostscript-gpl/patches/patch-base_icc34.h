$NetBSD$

--- base/icc34.h.orig	2012-02-08 08:48:47.000000000 +0000
+++ base/icc34.h
@@ -210,9 +210,9 @@ typedef __int32_t       icInt64Number[2]
 
 #include <sys/types.h>
 
-#if defined(__sun) || defined(__hpux) || defined (__MINGW) || defined(__MINGW32__)
+#if defined(__sun) || defined(__hpux) || defined (__MINGW) || defined(__MINGW32__) || defined(__QNXNTO__)
 
-#if defined (__MINGW) || defined(__MINGW32__)
+#if defined (__MINGW) || defined(__MINGW32__) || defined(__QNXNTO__)
 #include <stdint.h>
 #endif
 
