$NetBSD$

--- gettext-tools/gnulib-lib/strerror-override.h.orig	2013-03-05 08:40:52.000000000 +0000
+++ gettext-tools/gnulib-lib/strerror-override.h
@@ -50,7 +50,9 @@
      || GNULIB_defined_EILSEQ
 extern const char *strerror_override (int errnum);
 # else
+#  if 0 /* This breaks the compilation of strerror-override.c */
 #  define strerror_override(ignored) NULL
+#  endif
 # endif
 
 #endif /* _GL_STRERROR_OVERRIDE_H */
