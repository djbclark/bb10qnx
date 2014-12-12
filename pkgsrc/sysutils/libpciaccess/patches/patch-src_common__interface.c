$NetBSD$

--- src/common_interface.c.orig	2012-04-09 17:02:57.000000000 +0000
+++ src/common_interface.c
@@ -69,12 +69,16 @@
 
 #else
 
+#ifndef __QNXNTO__
 #include <sys/endian.h>
+#else
+#include <net/netbyte.h>
+#endif
 
 #define HTOLE_16(x)	htole16(x)
 #define HTOLE_32(x)	htole32(x)
 
-#if defined(__FreeBSD__) || defined(__DragonFly__) || defined(__NetBSD__)
+#if defined(__FreeBSD__) || defined(__DragonFly__) || defined(__NetBSD__) || defined(__QNXNTO__)
 #define LETOH_16(x)	le16toh(x)
 #define LETOH_32(x)	le32toh(x)
 #else
