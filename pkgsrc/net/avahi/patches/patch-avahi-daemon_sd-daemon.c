$NetBSD$

--- avahi-daemon/sd-daemon.c.orig	2011-02-18 22:58:22.000000000 +0000
+++ avahi-daemon/sd-daemon.c
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
