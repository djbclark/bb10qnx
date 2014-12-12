$NetBSD$

--- Python/bltinmodule.c.orig	2012-04-11 06:54:08.000000000 +0000
+++ Python/bltinmodule.c
@@ -21,7 +21,7 @@
 #if defined(MS_WINDOWS) && defined(HAVE_USABLE_WCHAR_T)
 const char *Py_FileSystemDefaultEncoding = "mbcs";
 int Py_HasFileSystemDefaultEncoding = 1;
-#elif defined(__APPLE__)
+#elif defined(__APPLE__) || defined(__QNXNTO__)
 const char *Py_FileSystemDefaultEncoding = "utf-8";
 int Py_HasFileSystemDefaultEncoding = 1;
 #elif defined(HAVE_LANGINFO_H) && defined(CODESET)
