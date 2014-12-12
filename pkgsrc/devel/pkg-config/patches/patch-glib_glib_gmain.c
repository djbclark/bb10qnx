$NetBSD$

--- glib/glib/gmain.c.orig	2012-05-14 22:06:02.000000000 +0000
+++ glib/glib/gmain.c
@@ -4393,7 +4393,10 @@ ensure_unix_signal_handler_installed_unl
 
   action.sa_handler = g_unix_signal_handler;
   sigemptyset (&action.sa_mask);
-  action.sa_flags = SA_RESTART | SA_NOCLDSTOP;
+  action.sa_flags = SA_NOCLDSTOP;
+#ifdef SA_RESTART
+  action.sa_flags |= SA_RESTART;
+#endif
   sigaction (signum, &action, NULL);
 }
 
