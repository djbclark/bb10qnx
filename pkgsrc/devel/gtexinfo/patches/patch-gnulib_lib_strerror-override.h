$NetBSD$

--- gnulib/lib/strerror-override.h.orig	2013-02-19 22:25:29.000000000 +0000
+++ gnulib/lib/strerror-override.h
@@ -50,7 +50,9 @@
      || GNULIB_defined_EILSEQ
 extern const char *strerror_override (int errnum);
 # else
+#  ifndef __QNXNTO__ /* This breaks the compilation of strerror-override.c */
 #  define strerror_override(ignored) NULL
+#  endif
 # endif
 
 #endif /* _GL_STRERROR_OVERRIDE_H */
