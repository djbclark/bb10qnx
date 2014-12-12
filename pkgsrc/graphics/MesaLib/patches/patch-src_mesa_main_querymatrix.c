$NetBSD$

--- src/mesa/main/querymatrix.c.orig	2011-10-15 00:43:58.000000000 +0000
+++ src/mesa/main/querymatrix.c
@@ -73,7 +73,7 @@ fpclassify(double x)
 #elif defined(__APPLE__) || defined(__CYGWIN__) || defined(__FreeBSD__) || \
      defined(__OpenBSD__) || defined(__NetBSD__) || defined(__DragonFly__) || \
      (defined(__sun) && defined(__C99FEATURES__)) || defined(__MINGW32__) || \
-     (defined(__sun) && defined(__GNUC__))
+     (defined(__sun) && defined(__GNUC__)) || defined(__QNXNTO__)
 
 /* fpclassify is available. */
 
