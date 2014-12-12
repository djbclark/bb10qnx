$NetBSD$

--- src/atoms.c.orig	2011-05-25 05:07:24.000000000 +0000
+++ src/atoms.c
@@ -8,6 +8,7 @@
 #include <xcb/xcb.h>
 #include <stdlib.h>
 #include <stdarg.h>
+#include <stdio.h>
 #include "xcb_atom.h"
 
 static char *makename(const char *fmt, ...)
