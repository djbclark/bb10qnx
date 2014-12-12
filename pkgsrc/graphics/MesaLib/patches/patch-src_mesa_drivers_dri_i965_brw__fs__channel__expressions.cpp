$NetBSD$

--- src/mesa/drivers/dri/i965/brw_fs_channel_expressions.cpp.orig	2011-10-15 00:43:58.000000000 +0000
+++ src/mesa/drivers/dri/i965/brw_fs_channel_expressions.cpp
@@ -41,6 +41,9 @@
  * we do retain the vector types in that case.
  */
 
+#ifdef __QNXNTO__
+#include <math.h> /* outside of extern "C"{} below */
+#endif
 extern "C" {
 #include "main/core.h"
 #include "brw_wm.h"
