$NetBSD$

--- src/mesa/drivers/dri/i965/brw_fs_vector_splitting.cpp.orig	2011-10-15 00:43:58.000000000 +0000
+++ src/mesa/drivers/dri/i965/brw_fs_vector_splitting.cpp
@@ -37,6 +37,9 @@
  * behavior we want for the results of texture lookups, but probably not for
  */
 
+#ifdef __QNXNTO__
+#include <math.h> /* outside of extern "C"{} below */
+#endif
 extern "C" {
 #include "main/core.h"
 #include "intel_context.h"
