$NetBSD$

--- ppp_fcs.h.orig	2006-02-13 03:07:43.000000000 +0000
+++ ppp_fcs.h
@@ -6,5 +6,23 @@
 
 #define PPPINITFCS16    0xffff  /* Initial FCS value */
 #define PPPGOODFCS16    0xf0b8  /* Good final FCS value */
+#ifdef __QNXNTO__
+#ifndef _U_INT8_T_DEFINED
+#define _U_INT8_T_DEFINED
+typedef _Uint8t         u_int8_t;
+#endif
+#ifndef _U_INT16_T_DEFINED
+#define _U_INT16_T_DEFINED
+typedef _Uint16t        u_int16_t;
+#endif
+#ifndef _U_INT32_T_DEFINED
+#define _U_INT32_T_DEFINED
+typedef _Uint32t        u_int32_t;
+#endif
+#ifndef _U_INT64_T_DEFINED
+#define _U_INT64_T_DEFINED
+typedef _Uint64t        u_int64_t;
+#endif
+#endif
 
 u_int16_t pppfcs16(u_int16_t fcs, void *cp, int len);
