$NetBSD$

--- src/mesa/drivers/dri/i965/brw_fs.cpp.orig	2011-10-15 00:43:58.000000000 +0000
+++ src/mesa/drivers/dri/i965/brw_fs.cpp
@@ -28,6 +28,9 @@
  * from the LIR.
  */
 
+#ifdef __QNXNTO__
+#include <math.h> /* outside of extern "C"{} below */
+#endif
 extern "C" {
 
 #include <sys/types.h>
