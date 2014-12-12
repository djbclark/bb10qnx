$NetBSD$

--- hw/xfree86/parser/write.c.orig	2012-08-02 00:15:46.000000000 +0000
+++ hw/xfree86/parser/write.c
@@ -68,6 +68,9 @@
 #if defined(SVR4) || defined(__linux__) || defined(CSRG_BASED)
 #define HAS_SAVED_IDS_AND_SETEUID
 #endif
+#ifndef HAS_SAVED_IDS_AND_SETEUID
+#include "os.h" /* For FatalError */
+#endif
 #if defined(WIN32)
 #define HAS_NO_UIDS
 #endif
