$NetBSD$

--- lib/strerror-override.h.orig	2012-06-03 17:35:39.000000000 +0000
+++ lib/strerror-override.h
@@ -49,7 +49,9 @@
      || GNULIB_defined_ENOTRECOVERABLE
 extern const char *strerror_override (int errnum);
 # else
+#  if 0 /* This breaks the compilation of strerror-override.c */
 #  define strerror_override(ignored) NULL
+#  endif
 # endif
 
 #endif /* _GL_STRERROR_OVERRIDE_H */
