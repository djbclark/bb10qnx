$NetBSD$

--- libdaemon/dsignal.c.orig	2009-04-20 00:58:07.000000000 +0000
+++ libdaemon/dsignal.c
@@ -83,7 +83,9 @@ int daemon_signal_install(int s){
     memset(&sa, 0, sizeof(sa));
     sa.sa_handler = _sigfunc;
     sigemptyset(&sa.sa_mask);
+#ifdef SA_RESTART
     sa.sa_flags = SA_RESTART;
+#endif
 
     if (sigaction(s, &sa, NULL) < 0) {
         daemon_log(LOG_ERR, "sigaction(%s, ...) failed: %s", strsignal(s), strerror(errno));
