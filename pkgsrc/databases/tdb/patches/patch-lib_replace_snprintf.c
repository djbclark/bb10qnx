$NetBSD$

--- lib/replace/snprintf.c.orig	2013-01-27 11:51:43.000000000 +0000
+++ lib/replace/snprintf.c
@@ -1257,6 +1257,17 @@ static int add_cnk_list_entry(struct pr_
 #endif 
 
 #if !defined(HAVE_VASPRINTF) || !defined(HAVE_C99_VSNPRINTF)
+#ifndef VA_COPY
+#ifdef HAVE_VA_COPY
+#define VA_COPY(dest, src) va_copy(dest, src)
+#else
+#ifdef HAVE___VA_COPY
+#define VA_COPY(dest, src) __va_copy(dest, src)
+#else
+#define VA_COPY(dest, src) (dest) = (src)
+#endif
+#endif
+#endif
  int rep_vasprintf(char **ptr, const char *format, va_list ap)
 {
 	int ret;
