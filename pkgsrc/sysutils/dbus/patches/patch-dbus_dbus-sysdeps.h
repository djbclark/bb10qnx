$NetBSD$

--- dbus/dbus-sysdeps.h.orig	2012-06-06 10:45:55.000000000 +0000
+++ dbus/dbus-sysdeps.h
@@ -264,6 +264,19 @@ dbus_int32_t _dbus_atomic_get (DBusAtomi
 #define _DBUS_POLLHUP     0x2000
 /** Invalid request: fd not open */
 #define _DBUS_POLLNVAL    0x8000
+#elif defined(__QNXNTO__)
+/** There is data to read */
+#define _DBUS_POLLIN      (0x0001 | 0x0004)
+/** There is urgent data to read */
+#define _DBUS_POLLPRI     0x0008
+/** Writing now will not block */
+#define _DBUS_POLLOUT     0x0002
+/** Error condition */
+#define _DBUS_POLLERR     0x0020
+/** Hung up */
+#define _DBUS_POLLHUP     0x0040
+/** Invalid request: fd not open */
+#define _DBUS_POLLNVAL    0x1000
 #elif defined(__HAIKU__)
 /** There is data to read */
 #define _DBUS_POLLIN      0x0001
