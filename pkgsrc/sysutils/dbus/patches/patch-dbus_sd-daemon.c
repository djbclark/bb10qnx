$NetBSD$

--- dbus/sd-daemon.c.orig	2012-06-06 10:45:55.000000000 +0000
+++ dbus/sd-daemon.c
@@ -32,7 +32,11 @@
 #include <sys/stat.h>
 #include <sys/socket.h>
 #include <sys/un.h>
+#ifndef __QNXNTO__
 #include <sys/fcntl.h>
+#else
+#include <fcntl.h>
+#endif
 #include <netinet/in.h>
 #include <stdlib.h>
 #include <errno.h>
