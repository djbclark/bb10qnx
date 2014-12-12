$NetBSD$

--- src/gui.c.orig	2012-11-22 14:18:52.000000000 +0000
+++ src/gui.c
@@ -206,7 +206,7 @@ gui_attempt_start()
     static void
 gui_do_fork()
 {
-#ifdef __QNXNTO__
+#if 0
     procmgr_daemon(0, PROCMGR_DAEMON_KEEPUMASK | PROCMGR_DAEMON_NOCHDIR |
 	    PROCMGR_DAEMON_NOCLOSE | PROCMGR_DAEMON_NODEVNULL);
     gui_attempt_start();
