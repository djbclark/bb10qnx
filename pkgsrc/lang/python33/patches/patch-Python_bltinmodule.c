$NetBSD$

--- Python/bltinmodule.c.orig	2012-09-29 08:00:48.000000000 +0000
+++ Python/bltinmodule.c
@@ -24,7 +24,7 @@
 #ifdef HAVE_MBCS
 const char *Py_FileSystemDefaultEncoding = "mbcs";
 int Py_HasFileSystemDefaultEncoding = 1;
-#elif defined(__APPLE__)
+#elif defined(__APPLE__) || defined(__QNXNTO__)
 const char *Py_FileSystemDefaultEncoding = "utf-8";
 int Py_HasFileSystemDefaultEncoding = 1;
 #else
