$NetBSD$

--- lib/strutil/strutilutf8.c.orig	2010-11-08 11:46:13.000000000 +0000
+++ lib/strutil/strutilutf8.c
@@ -27,7 +27,9 @@
 #include <stdio.h>
 #include <errno.h>
 #include <glib.h>
+#ifndef __QNXNTO__
 #include <langinfo.h>
+#endif
 #include <string.h>
 
 #include "lib/global.h"
