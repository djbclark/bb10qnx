$NetBSD$

--- src/corelib/io/qprocess_unix.cpp.orig	2014-01-17 19:37:16.000000000 +0000
+++ src/corelib/io/qprocess_unix.cpp
@@ -40,7 +40,9 @@
 ****************************************************************************/
 
 //#define QPROCESS_DEBUG
-#include <stdint.h>
+#ifdef __QNXNTO__
+#include <sys/part.h>
+#endif
 #include "qdebug.h"
 
 #ifndef QT_NO_PROCESS
