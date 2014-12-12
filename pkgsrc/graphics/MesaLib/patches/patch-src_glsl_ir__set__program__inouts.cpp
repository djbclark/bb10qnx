$NetBSD$

--- src/glsl/ir_set_program_inouts.cpp.orig	2011-10-15 00:43:58.000000000 +0000
+++ src/glsl/ir_set_program_inouts.cpp
@@ -34,6 +34,9 @@
  * from the GLSL IR.
  */
 
+#ifdef __QNXNTO__
+#include <math.h> /* outside of extern "C"{} below */
+#endif
 extern "C" {
 #include "main/core.h" /* for struct gl_program */
 #include "program/hash_table.h"
