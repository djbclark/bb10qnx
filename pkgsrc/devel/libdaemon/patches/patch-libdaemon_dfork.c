$NetBSD$

--- libdaemon/dfork.c.orig	2009-10-18 01:56:10.000000000 +0000
+++ libdaemon/dfork.c
@@ -137,7 +137,9 @@ pid_t daemon_fork(void) {
 
     memset(&sa_new, 0, sizeof(sa_new));
     sa_new.sa_handler = sigchld;
+#ifdef SA_RESTART
     sa_new.sa_flags = SA_RESTART;
+#endif
 
     if (sigemptyset(&ss_new) < 0) {
         daemon_log(LOG_ERR, "sigemptyset() failed: %s", strerror(errno));
