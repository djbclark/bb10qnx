$NetBSD: patch-ipc_chromium_src_build_build__config.h,v 1.1 2013/07/17 11:00:13 jperkin Exp $

--- ipc/chromium/src/build/build_config.h.orig	2013-06-18 11:01:23.000000000 +0000
+++ ipc/chromium/src/build/build_config.h
@@ -27,8 +27,12 @@
 #define OS_NETBSD 1
 #elif defined(__OpenBSD__)
 #define OS_OPENBSD 1
+#elif defined(__sun)
+#define OS_SOLARIS 1
 #elif defined(_WIN32)
 #define OS_WIN 1
+#elif defined(__QNXNTO__)
+#define OS_QNX1
 #else
 #error Please add support for your platform in build/build_config.h
 #endif
@@ -42,7 +46,7 @@
 
 // For access to standard POSIX features, use OS_POSIX instead of a more
 // specific macro.
-#if defined(OS_MACOSX) || defined(OS_LINUX) || defined(OS_BSD)
+#if defined(OS_MACOSX) || defined(OS_LINUX) || defined(OS_BSD) || defined(OS_SOLARIS) || defined(OS_QNX)
 #define OS_POSIX 1
 #endif
 
