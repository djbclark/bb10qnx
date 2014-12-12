$NetBSD$

--- src/el.c.orig	2013-07-10 14:09:39.000000000 +0000
+++ src/el.c
@@ -55,7 +55,9 @@ __RCSID("$NetBSD: el.c,v 1.72 2013/01/22
 #include <stdarg.h>
 #include <ctype.h>
 #include <locale.h>
+#ifdef WIDECHAR
 #include <langinfo.h>
+#endif
 #include "el.h"
 
 #ifndef HAVE_SECURE_GETENV
