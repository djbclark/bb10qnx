$NetBSD$

--- lib/strerror-override.h.orig	2012-12-22 07:22:58.000000000 +0000
+++ lib/strerror-override.h
@@ -50,7 +50,9 @@
      || GNULIB_defined_EILSEQ
 extern const char *strerror_override (int errnum);
 # else
+#  ifndef __QNXNTO__ /* This breaks the compilation of strerror-override.c */
 #  define strerror_override(ignored) NULL
+#  endif
 # endif
 
 #endif /* _GL_STRERROR_OVERRIDE_H */
