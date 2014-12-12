$NetBSD: patch-media_libpng_pngpriv.h,v 1.1 2013/07/17 11:00:13 jperkin Exp $

--- media/libpng/pngpriv.h.orig	2013-05-11 19:19:43.000000000 +0000
+++ media/libpng/pngpriv.h
@@ -38,6 +38,7 @@
  * still required (as of 2011-05-02.)
  */
 #define _POSIX_SOURCE 1 /* Just the POSIX 1003.1 and C89 APIs */
+#define _XOPEN_SOURCE 600
 
 /* This is required for the definition of abort(), used as a last ditch
  * error handler when all else fails.
