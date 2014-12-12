$NetBSD: patch-ipc_chromium_src_base_debug__util__posix.cc,v 1.1 2013/07/17 11:00:13 jperkin Exp $

--- ipc/chromium/src/base/debug_util_posix.cc.orig	2013-06-18 11:01:23.000000000 +0000
+++ ipc/chromium/src/base/debug_util_posix.cc
@@ -107,7 +107,7 @@ bool DebugUtil::BeingDebugged() {
   return being_debugged;
 }
 
-#elif defined(OS_LINUX)
+#elif defined(OS_LINUX) || defined(OS_SOLARIS)
 
 // We can look in /proc/self/status for TracerPid.  We are likely used in crash
 // handling, so we are careful not to use the heap or have side effects.
@@ -142,7 +142,25 @@ bool DebugUtil::BeingDebugged() {
   return pid_index < status.size() && status[pid_index] != '0';
 }
 
-#endif  // OS_LINUX
+#elif defined(OS_QNX)
+bool DebugUtil::BeingDebugged() {
+	int fd, rc;
+
+	/*
+	 * Only one O_RDWR is allowed at any point in time.
+	 * If we get EBUSY, assume it's the debugger.
+	 */
+	rc = false;
+	if ((fd = open("/proc/self/as", O_RDWR)) == -1) {
+		if (errno == EBUSY)
+			rc = true;
+	} else {
+		close(fd);
+	}
+	return rc;
+}
+
+#endif
 
 // static
 void DebugUtil::BreakDebugger() {
