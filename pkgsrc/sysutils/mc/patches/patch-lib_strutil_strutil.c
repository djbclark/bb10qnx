$NetBSD$

--- lib/strutil/strutil.c.orig	2010-11-08 11:46:13.000000000 +0000
+++ lib/strutil/strutil.c
@@ -25,7 +25,9 @@
 #include <config.h>
 #include <stdlib.h>
 #include <stdio.h>
+#ifndef __QNXNTO__
 #include <langinfo.h>
+#endif
 #include <string.h>
 #include <errno.h>
 #include <stdarg.h>
@@ -323,7 +325,11 @@ str_translate_char (GIConv conv, const c
 const char *
 str_detect_termencoding (void)
 {
+#ifndef __QNXNTO__
     return (nl_langinfo (CODESET));
+#else
+    return "C";
+#endif
 }
 
 static int
