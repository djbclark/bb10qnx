$NetBSD$

--- Python/pythonrun.c.orig	2013-04-06 14:02:40.000000000 +0000
+++ Python/pythonrun.c
@@ -27,6 +27,9 @@
 #include "malloc.h" /* for alloca */
 #endif
 
+#ifdef __QNXNTO__
+#include <locale.h>
+#endif
 #ifdef HAVE_LANGINFO_H
 #include <locale.h>
 #include <langinfo.h>
@@ -146,7 +149,7 @@ Py_InitializeEx(int install_sigs)
     int free_codeset = 0;
     int overridden = 0;
     PyObject *sys_stream, *sys_isatty;
-#if defined(Py_USING_UNICODE) && defined(HAVE_LANGINFO_H) && defined(CODESET)
+#if defined(Py_USING_UNICODE) && ((defined(HAVE_LANGINFO_H) && defined(CODESET)) || defined(__QNXNTO__))
     char *saved_locale, *loc_codeset;
 #endif
 #ifdef MS_WINDOWS
@@ -275,7 +278,7 @@ Py_InitializeEx(int install_sigs)
         overridden = 1;
     }
 
-#if defined(Py_USING_UNICODE) && defined(HAVE_LANGINFO_H) && defined(CODESET)
+#if defined(Py_USING_UNICODE) && ((defined(HAVE_LANGINFO_H) && defined(CODESET)) || defined(__QNXNTO__))
     /* On Unix, set the file system encoding according to the
        user's preference, if the CODESET names a well-known
        Python codec, and Py_FileSystemDefaultEncoding isn't
@@ -285,7 +288,11 @@ Py_InitializeEx(int install_sigs)
     if (!overridden || !Py_FileSystemDefaultEncoding) {
         saved_locale = strdup(setlocale(LC_CTYPE, NULL));
         setlocale(LC_CTYPE, "");
+#if !defined(__QNXNTO__) || defined(HAVE_LANGINFO_H)
         loc_codeset = nl_langinfo(CODESET);
+#else
+	loc_codeset = "C";
+#endif
         if (loc_codeset && *loc_codeset) {
             PyObject *enc = PyCodec_Encoder(loc_codeset);
             if (enc) {
