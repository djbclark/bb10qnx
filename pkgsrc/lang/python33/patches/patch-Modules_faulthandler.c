$NetBSD$

--- Modules/faulthandler.c.orig	2012-09-29 08:00:45.000000000 +0000
+++ Modules/faulthandler.c
@@ -600,7 +600,10 @@ faulthandler_register(int signum, int ch
     /* if the signal is received while the kernel is executing a system
        call, try to restart the system call instead of interrupting it and
        return EINTR. */
-    action.sa_flags = SA_RESTART;
+    action.sa_flags = 0;
+#ifdef SA_RESTART
+    action.sa_flags |= SA_RESTART;
+#endif
     if (chain) {
         /* do not prevent the signal from being received from within its
            own signal handler */
