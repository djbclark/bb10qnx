$NetBSD$

--- extra/yassl/include/lock.hpp.orig	2011-02-11 19:20:22.000000000 +0000
+++ extra/yassl/include/lock.hpp
@@ -32,6 +32,9 @@
 #include <windows.h>
 #endif
 #endif
+#ifdef __QNXNTO__
+#include <pthread.h> /* This has to be outside the namespace yaSSL below */
+#endif
 
 namespace yaSSL {
 
