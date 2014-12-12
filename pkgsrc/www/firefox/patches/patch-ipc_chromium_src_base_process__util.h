$NetBSD: patch-ipc_chromium_src_base_process__util.h,v 1.1 2013/07/17 11:00:13 jperkin Exp $

--- ipc/chromium/src/base/process_util.h.orig	2013-06-18 11:01:23.000000000 +0000
+++ ipc/chromium/src/base/process_util.h
@@ -13,7 +13,7 @@
 #if defined(OS_WIN)
 #include <windows.h>
 #include <tlhelp32.h>
-#elif defined(OS_LINUX)
+#elif defined(OS_LINUX) || defined(OS_SOLARIS)
 #include <dirent.h>
 #include <limits.h>
 #include <sys/types.h>
@@ -32,6 +32,9 @@
 typedef PROCESSENTRY32 ProcessEntry;
 typedef IO_COUNTERS IoCounters;
 #elif defined(OS_POSIX)
+#ifndef NAME_MAX
+#define NAME_MAX _POSIX_NAME_MAX
+#endif
 // TODO(port): we should not rely on a Win32 structure.
 struct ProcessEntry {
   int pid;
@@ -298,7 +301,7 @@ class NamedProcessIterator {
   const ProcessEntry* NextProcessEntry();
 
  private:
-#if !defined(OS_BSD)
+#if !defined(OS_BSD) && !defined(OS_QNX)
   // Determines whether there's another process (regardless of executable)
   // left in the list of all processes.  Returns true and sets entry_ to
   // that process's info if there is one, false otherwise.
@@ -316,9 +319,9 @@ class NamedProcessIterator {
 #if defined(OS_WIN)
   HANDLE snapshot_;
   bool started_iteration_;
-#elif defined(OS_LINUX)
+#elif defined(OS_LINUX) || defined(OS_SOLARIS)
   DIR *procfs_dir_;
-#elif defined(OS_BSD)
+#elif defined(OS_BSD) || defined(OS_QNX)
   std::vector<ProcessEntry> content;
   size_t nextEntry;
 #elif defined(OS_MACOSX)
