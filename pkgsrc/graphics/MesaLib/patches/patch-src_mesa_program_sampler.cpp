$NetBSD$

--- src/mesa/program/sampler.cpp.orig	2011-10-15 00:43:58.000000000 +0000
+++ src/mesa/program/sampler.cpp
@@ -23,6 +23,9 @@
  * DEALINGS IN THE SOFTWARE.
  */
 
+#ifdef __QNXNTO__
+#include <math.h> /* outside of extern "C"{} below */
+#endif
 #include "ir.h"
 #include "glsl_types.h"
 #include "ir_visitor.h"
