$NetBSD$

--- lib/tty/tty.c.orig	2010-11-08 11:46:13.000000000 +0000
+++ lib/tty/tty.c
@@ -88,7 +88,10 @@ tty_start_interrupt_key (void)
 
     act.sa_handler = sigintr_handler;
     sigemptyset (&act.sa_mask);
-    act.sa_flags = SA_RESTART;
+    act.sa_flags = 0;
+#ifdef SA_RESTART
+    act.sa_flags |= SA_RESTART;
+#endif
     sigaction (SIGINT, &act, NULL);
 }
 
