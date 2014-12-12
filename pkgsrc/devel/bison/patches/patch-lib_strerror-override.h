$NetBSD$

--- lib/strerror-override.h.orig	2013-04-08 09:18:57.000000000 +0000
+++ lib/strerror-override.h
@@ -47,7 +47,7 @@
      || GNULIB_defined_ECANCELED \
      || GNULIB_defined_EOWNERDEAD \
      || GNULIB_defined_ENOTRECOVERABLE \
-     || GNULIB_defined_EILSEQ
+     || GNULIB_defined_EILSEQ || defined(__QNXNTO__)
 extern const char *strerror_override (int errnum);
 # else
 #  define strerror_override(ignored) NULL
