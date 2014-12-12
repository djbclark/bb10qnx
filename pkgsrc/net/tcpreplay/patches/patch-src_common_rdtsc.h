$NetBSD$

--- src/common/rdtsc.h.orig	2009-01-18 17:47:37.000000000 +0000
+++ src/common/rdtsc.h
@@ -42,6 +42,10 @@
 #ifndef __RDTSC_H__
 #define __RDTSC_H__
 
+#ifdef __QNXNTO__
+#include <time.h>
+#endif
+
 
 u_int64_t rdtsc_calibrate(u_int32_t mhz);
 
