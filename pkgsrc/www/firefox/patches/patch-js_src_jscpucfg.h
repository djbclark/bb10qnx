$NetBSD$

--- js/src/jscpucfg.h.orig	2013-06-18 11:01:26.000000000 +0000
+++ js/src/jscpucfg.h
@@ -44,6 +44,21 @@
 #  define IS_BIG_ENDIAN 1
 # endif
 
+#elif defined(__QNXNTO__)
+#include <sys/param.h>
+
+#if defined(BYTE_ORDER)
+#if BYTE_ORDER == LITTLE_ENDIAN
+#define IS_LITTLE_ENDIAN 1
+#undef  IS_BIG_ENDIAN
+#elif BYTE_ORDER == BIG_ENDIAN
+#undef  IS_LITTLE_ENDIAN
+#define IS_BIG_ENDIAN 1
+#endif
+#else /* !defined(BYTE_ORDER) */
+#error "sys/param.h does not define BYTE_ORDER. Cannot determine endianness."
+#endif
+
 #elif defined(JS_HAVE_ENDIAN_H)
 # include <endian.h>
 
