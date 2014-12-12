$NetBSD$

--- tools/tdbbackup.c.orig	2012-04-11 12:36:12.000000000 +0000
+++ tools/tdbbackup.c
@@ -51,6 +51,13 @@
 #include <getopt.h>
 #endif
 
+#ifdef __QNXNTO__
+/*
+ * This gets defined to rep_snprintf by replace subsystem but I
+ * can't figure out how to get it linked in.
+ */
+#undef snprintf
+#endif
 static int failed;
 
 static struct tdb_logging_context log_ctx;
