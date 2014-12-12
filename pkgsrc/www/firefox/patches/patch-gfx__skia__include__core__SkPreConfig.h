$NetBSD: patch-gfx__skia__include__core__SkPreConfig.h,v 1.1 2013/06/21 23:11:42 ryoon Exp $

Configure sparc cpus as big endian (Bugzilla #884376)

diff -r 581ea0e6531e gfx/skia/include/core/SkPreConfig.h
--- gfx/skia/include/core/SkPreConfig.h.orig	2013-06-18 11:01:20.000000000 +0000
+++ gfx/skia/include/core/SkPreConfig.h
@@ -36,7 +36,7 @@
         #define SK_BUILD_FOR_ANDROID
     #elif defined(linux) || defined(__FreeBSD__) || defined(__OpenBSD__) || \
           defined(__sun) || defined(__NetBSD__) || defined(__DragonFly__) || \
-          defined(__GLIBC__) || defined(__GNU__)
+          defined(__GLIBC__) || defined(__GNU__) || defined(__QNXNTO__)
         #define SK_BUILD_FOR_UNIX
     #elif TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
         #define SK_BUILD_FOR_IOS
@@ -94,7 +94,7 @@
 //////////////////////////////////////////////////////////////////////
 
 #if !defined(SK_CPU_BENDIAN) && !defined(SK_CPU_LENDIAN)
-#if defined (__ppc__) || defined(__PPC__) || defined(__ppc64__) || defined(__PPC64__)
+#if defined (__ppc__) || defined(__PPC__) || defined(__ppc64__) || defined(__PPC64__) || defined(__sparc) || defined(__sparc__)
         #define SK_CPU_BENDIAN
     #else
         #define SK_CPU_LENDIAN
