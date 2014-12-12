$NetBSD: patch-ipc_chromium_src_base_process__util__posix.cc,v 1.1 2013/07/17 11:00:13 jperkin Exp $

--- ipc/chromium/src/base/process_util_posix.cc.orig	2013-06-18 11:01:23.000000000 +0000
+++ ipc/chromium/src/base/process_util_posix.cc
@@ -110,13 +110,13 @@ void CloseSuperfluousFds(const base::Inj
 #if defined(ANDROID)
   static const rlim_t kSystemDefaultMaxFds = 1024;
   static const char kFDDir[] = "/proc/self/fd";
-#elif defined(OS_LINUX)
+#elif defined(OS_LINUX) || defined(OS_SOLARIS)
   static const rlim_t kSystemDefaultMaxFds = 8192;
   static const char kFDDir[] = "/proc/self/fd";
 #elif defined(OS_MACOSX)
   static const rlim_t kSystemDefaultMaxFds = 256;
   static const char kFDDir[] = "/dev/fd";
-#elif defined(OS_BSD)
+#elif defined(OS_BSD) || defined(OS_QNX)
   // the getrlimit below should never fail, so whatever ..
   static const rlim_t kSystemDefaultMaxFds = 1024;
   // at least /dev/fd will exist
@@ -202,7 +202,8 @@ void CloseSuperfluousFds(const base::Inj
 // TODO(agl): Remove this function. It's fundamentally broken for multithreaded
 // apps.
 void SetAllFDsToCloseOnExec() {
-#if defined(OS_LINUX)
+#if !defined(OS_QNX)
+#if defined(OS_LINUX) || defined(OS_SOLARIS)
   const char fd_dir[] = "/proc/self/fd";
 #elif defined(OS_MACOSX) || defined(OS_BSD)
   const char fd_dir[] = "/dev/fd";
@@ -229,6 +230,17 @@ void SetAllFDsToCloseOnExec() {
       DLOG(ERROR) << "fcntl failure.";
     }
   }
+#else
+
+  int i, flags;
+
+  for (i = STDERR_FILENO + 1; i < 1024; i++) {
+    int flags = fcntl(i, F_GETFD);
+    if (flags == -1)
+      continue;
+   fcntl(i, F_SETFD, flags | FD_CLOEXEC);
+  }
+#endif
 }
 
 ProcessMetrics::ProcessMetrics(ProcessHandle process) : process_(process),
