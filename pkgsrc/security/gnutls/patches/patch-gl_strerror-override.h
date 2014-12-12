$NetBSD$

--- gl/strerror-override.h.orig	2013-03-04 05:41:51.000000000 +0000
+++ gl/strerror-override.h
@@ -50,7 +50,9 @@
      || GNULIB_defined_EILSEQ
 extern const char *strerror_override (int errnum);
 # else
+#ifndef __QNXNTO__
 #  define strerror_override(ignored) NULL
+#endif
 # endif
 
 #endif /* _GL_STRERROR_OVERRIDE_H */
