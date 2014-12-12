$NetBSD$

--- src/mesa/main/ff_fragment_shader.cpp.orig	2011-10-15 00:43:58.000000000 +0000
+++ src/mesa/main/ff_fragment_shader.cpp
@@ -26,6 +26,9 @@
  * 
  **************************************************************************/
 
+#ifdef __QNXNTO__
+#include <math.h> /* outside of extern "C"{} below */
+#endif
 extern "C" {
 #include "glheader.h"
 #include "imports.h"
