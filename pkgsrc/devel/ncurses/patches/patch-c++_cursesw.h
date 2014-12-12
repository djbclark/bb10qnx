$NetBSD$

--- c++/cursesw.h.orig	2008-01-19 21:09:10.000000000 +0000
+++ c++/cursesw.h
@@ -35,6 +35,10 @@
 
 #include <etip.h>
 
+#ifdef __QNXNTO__
+#include <wchar.h> /* outside of extern "C"{} below */
+#endif
+
 extern "C" {
 #  include   <curses.h>
 }
