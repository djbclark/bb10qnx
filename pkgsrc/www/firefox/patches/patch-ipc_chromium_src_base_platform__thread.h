$NetBSD: patch-ipc_chromium_src_base_platform__thread.h,v 1.1 2013/07/17 11:00:13 jperkin Exp $

--- ipc/chromium/src/base/platform_thread.h.orig	2013-06-18 11:01:23.000000000 +0000
+++ ipc/chromium/src/base/platform_thread.h
@@ -25,12 +25,17 @@ typedef pthread_t PlatformThreadHandle;
 #if defined(OS_LINUX) || defined(OS_OPENBSD)
 #include <unistd.h>
 typedef pid_t PlatformThreadId;
+#elif defined(OS_SOLARIS)
+#include <sys/lwp.h>
+typedef lwpid_t PlatformThreadId;
 #elif defined(OS_BSD)
 #include <sys/types.h>
 typedef lwpid_t PlatformThreadId;
 #elif defined(OS_MACOSX)
 #include <mach/mach.h>
 typedef mach_port_t PlatformThreadId;
+#elif defined(OS_QNX)
+typedef pthread_t PlatformThreadId;
 #endif
 #endif
 
