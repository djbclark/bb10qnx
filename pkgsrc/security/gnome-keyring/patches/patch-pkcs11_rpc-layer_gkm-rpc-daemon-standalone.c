$NetBSD$

--- pkcs11/rpc-layer/gkm-rpc-daemon-standalone.c.orig	2010-10-19 02:11:38.000000000 +0000
+++ pkcs11/rpc-layer/gkm-rpc-daemon-standalone.c
@@ -35,6 +35,9 @@
 
 #include <dlfcn.h>
 #include <pthread.h>
+#ifdef __QNXNTO__
+#include <sys/select.h>
+#endif
 
 #define SOCKET_PATH "/tmp/gkm-rpc-daemon.sock"
 
