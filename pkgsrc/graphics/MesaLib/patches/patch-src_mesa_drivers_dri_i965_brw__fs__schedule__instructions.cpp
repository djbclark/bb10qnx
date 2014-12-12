$NetBSD$

--- src/mesa/drivers/dri/i965/brw_fs_schedule_instructions.cpp.orig	2011-10-15 00:43:58.000000000 +0000
+++ src/mesa/drivers/dri/i965/brw_fs_schedule_instructions.cpp
@@ -25,6 +25,9 @@
  *
  */
 
+#ifdef __QNXNTO__
+#include <math.h> /* outside of extern "C"{} below */
+#endif
 extern "C" {
 
 #include <sys/types.h>
