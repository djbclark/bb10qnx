$NetBSD$

--- pptp_ctrl.h.orig	2006-02-13 03:07:43.000000000 +0000
+++ pptp_ctrl.h
@@ -7,6 +7,25 @@
 #ifndef INC_PPTP_CTRL_H
 #define INC_PPTP_CTRL_H
 #include <sys/types.h>
+#ifdef __QNXNTO__
+#include <sys/select.h>
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
 
 typedef struct PPTP_CONN PPTP_CONN;
 typedef struct PPTP_CALL PPTP_CALL;
