$NetBSD$

--- lib/replace/test/snprintf.c.orig	2012-04-11 12:36:12.000000000 +0000
+++ lib/replace/test/snprintf.c
@@ -1,3 +1,6 @@
+#ifdef __QNXNTO__
+#include <stdarg.h>
+#endif
 void foo(const char *format, ...)
 {
 	va_list ap;
@@ -20,8 +23,12 @@ void foo(const char *format, ...)
 
 	if (snprintf(buf, 20, "%lld", l) != 12 || strcmp(buf, "123456789000") != 0) exit(4);
 	if (snprintf(buf, 20, "%zu", 123456789) != 9 || strcmp(buf, "123456789") != 0) exit(5);
+#ifndef __QNXNTO__
 	if (snprintf(buf, 20, "%2\$d %1\$d", 3, 4) != 3 || strcmp(buf, "4 3") != 0) exit(6);
 	if (snprintf(buf, 20, "%s", 0) < 3) exit(7);
+#else
+	/* Positional parameters arent used anywhere here at time of writing */
+#endif
 
 	printf("1");
 	exit(0);
