$NetBSD$

--- doc/examples/ex-cxx.cpp.orig	2012-10-26 18:48:30.000000000 +0000
+++ doc/examples/ex-cxx.cpp
@@ -1,3 +1,6 @@
+#ifdef __QNXNTO__
+#define GNULIB_NAMESPACE
+#endif
 #include <config.h>
 #include <iostream>
 #include <stdexcept>
