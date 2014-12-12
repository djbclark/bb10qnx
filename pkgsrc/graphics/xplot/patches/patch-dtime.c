$NetBSD$

--- dtime.c.orig	1998-06-18 17:50:41.000000000 +0000
+++ dtime.c
@@ -33,7 +33,9 @@ to preserve same.
 #include "xplot.h"
 #include <stdio.h>
 
+#ifndef __QNXNTO__
 extern double atof();
+#endif
 #if defined(linux) || defined(ultrix)
 #define remainder drem
 #endif
