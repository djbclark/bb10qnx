$NetBSD$

--- src/mesa/drivers/dri/i965/brw_fs_emit.cpp.orig	2011-10-15 00:43:58.000000000 +0000
+++ src/mesa/drivers/dri/i965/brw_fs_emit.cpp
@@ -27,6 +27,9 @@
  * native instructions.
  */
 
+#ifdef __QNXNTO__
+#include <math.h> /* outside of extern "C"{} below */
+#endif
 extern "C" {
 #include "main/macros.h"
 #include "brw_context.h"
