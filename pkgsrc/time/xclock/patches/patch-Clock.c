$NetBSD$

--- Clock.c.orig	2011-10-06 04:55:01.000000000 +0000
+++ Clock.c
@@ -89,7 +89,9 @@ SOFTWARE.
 #include <X11/Xaw/XawInit.h>
 #if !defined(NO_I18N) && defined(HAVE_ICONV)
 #include <iconv.h>
+#ifndef __QNXNTO__
 #include <langinfo.h>
+#endif
 #include <errno.h>
 #include <limits.h>
 #endif
@@ -2217,7 +2219,11 @@ clock_to_utf8(const char *str, int in_le
     ICONV_CONST char *inptr;
     char *outptr;
     size_t ret;
+#ifndef __QNXNTO__
     const char *code_set = nl_langinfo(CODESET);
+#else
+    const char *code_set = "C";
+#endif
 
     if (str == NULL ||code_set == NULL || strcasecmp(code_set, "646") == 0)
     	return NULL;
