$NetBSD$

--- tools/tdbtorture.c.orig	2012-04-11 12:36:12.000000000 +0000
+++ tools/tdbtorture.c
@@ -35,6 +35,53 @@ static int loopnum;
 static int count_pipe;
 static struct tdb_logging_context log_ctx;
 
+
+
+
+#ifdef __QNXNTO__
+
+#undef asprintf
+#undef vasprintf
+#undef vsnprintf
+
+//#include <nbutil.h>
+#include <stdarg.h>
+#include <malloc.h>
+
+static int
+vasprintf(char ** __restrict bufp, const char * __restrict fmt, va_list va)
+{
+	va_list va_new;
+	int required;
+
+	va_copy(va_new, va);
+	required = vsnprintf(NULL, 0, fmt, va_new);
+	va_end(va_new);
+
+	required++; /* for terminating '\0' */
+
+	if ((*bufp = malloc(required)) == NULL)
+		return -1;
+
+	return (vsnprintf(*bufp, required, fmt, va));
+}
+
+static int
+asprintf(char ** __restrict bufp, const char * __restrict fmt, ...)
+{
+	va_list va;
+	int ret;
+
+	va_start(va, fmt);
+	ret = vasprintf(bufp, fmt, va);
+	va_end(va);
+
+	return (ret);
+}
+
+
+#endif
+
 #ifdef PRINTF_ATTRIBUTE
 static void tdb_log(struct tdb_context *tdb, enum tdb_debug_level level, const char *format, ...) PRINTF_ATTRIBUTE(3,4);
 #endif
