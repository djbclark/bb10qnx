$NetBSD$

--- lib/ipc/server.c.orig	2012-01-10 21:53:51.000000000 +0000
+++ lib/ipc/server.c
@@ -36,6 +36,10 @@
 #include "hi_locl.h"
 #include <assert.h>
 
+#if defined(__QNXNTO__) && !defined(NGROUPS)
+#define NGROUPS NGROUPS_MAX
+#endif
+
 #define MAX_PACKET_SIZE (128 * 1024)
 
 struct heim_sipc {
