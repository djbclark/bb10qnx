$NetBSD$

--- hw/xfree86/common/xf86Configure.c.orig	2012-05-17 17:09:03.000000000 +0000
+++ hw/xfree86/common/xf86Configure.c
@@ -40,6 +40,9 @@
 #include "xf86Sbus.h"
 #endif
 #include "misc.h"
+#ifdef __QNXNTO__
+#include <errno.h>
+#endif
 
 typedef struct _DevToConfig {
     GDevRec GDev;
@@ -66,6 +69,9 @@ static const char *DFLT_MOUSE_PROTO = "a
 #elif defined(WSCONS_SUPPORT)
 static const char *DFLT_MOUSE_DEV = "/dev/wsmouse";
 static const char *DFLT_MOUSE_PROTO = "wsmouse";
+#elif defined(__QNXNTO__)
+static char DFLT_MOUSE_DEV[] = "/dev/devi/mouse0";
+static char DFLT_MOUSE_PROTO[] = "hid";
 #else
 static const char *DFLT_MOUSE_DEV = "/dev/mouse";
 static const char *DFLT_MOUSE_PROTO = "auto";
