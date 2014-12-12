$NetBSD$

--- xwininfo.c.orig	2011-06-18 17:20:51.000000000 +0000
+++ xwininfo.c
@@ -76,7 +76,9 @@ of the copyright holder.
 #include <stdlib.h>
 #include <string.h>
 #include <locale.h>
+#ifndef __QNXNTO__
 #include <langinfo.h>
+#endif
 #ifdef HAVE_ICONV
 # include <iconv.h>
 #endif
@@ -439,7 +441,11 @@ main (int argc, char **argv)
 
     if (!setlocale (LC_ALL, ""))
 	fprintf (stderr, "%s: can not set locale properly\n", program_name);
+#ifndef __QNXNTO__
     user_encoding = nl_langinfo (CODESET);
+#else
+    user_encoding = NULL;
+#endif
     if (user_encoding == NULL)
 	user_encoding = "unknown encoding";
 
