$NetBSD$

--- src/mesa/drivers/dri/i965/brw_fs_visitor.cpp.orig	2011-10-15 04:29:59.000000000 +0000
+++ src/mesa/drivers/dri/i965/brw_fs_visitor.cpp
@@ -27,6 +27,9 @@
  * makes it easier to do backend-specific optimizations than doing so
  * in the GLSL IR or in the native code.
  */
+#ifdef __QNXNTO__
+#include <math.h> /* outside of extern "C"{} below */
+#endif
 extern "C" {
 
 #include <sys/types.h>
