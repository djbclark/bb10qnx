$NetBSD$

--- git-compat-util.h.orig	2013-04-07 22:52:04.000000000 +0000
+++ git-compat-util.h
@@ -169,6 +169,9 @@ typedef unsigned long uintptr_t;
 #undef _ALL_SOURCE /* AIX 5.3L defines a struct list with _ALL_SOURCE. */
 #include <grp.h>
 #define _ALL_SOURCE 1
+#if defined(__QNXNTO__)
+#include "compat/qnxnto.h"
+#endif
 #endif
 #endif
 
