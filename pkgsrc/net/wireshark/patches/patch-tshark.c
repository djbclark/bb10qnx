$NetBSD$

--- tshark.c.orig	2012-06-21 16:36:12.000000000 +0000
+++ tshark.c
@@ -2055,7 +2055,10 @@ capture(void)
      pipe, pick up the exit status, and quit. */
   memset(&action, 0, sizeof(action));
   action.sa_handler = capture_cleanup;
-  action.sa_flags = SA_RESTART;
+  action.sa_flags = 0;
+#ifdef SA_RESTART
+  action.sa_flags |= SA_RESTART;
+#endif
   sigemptyset(&action.sa_mask);
   sigaction(SIGTERM, &action, NULL);
   sigaction(SIGINT, &action, NULL);
@@ -2070,7 +2073,10 @@ capture(void)
      Again, restart any read that was in progress, so that it doesn't
      disrupt reading from the sync pipe. */
   action.sa_handler = report_counts_siginfo;
-  action.sa_flags = SA_RESTART;
+  action.sa_flags = 0;
+#ifdef SA_RESTART
+  action.sa_flags |= SA_RESTART;
+#endif
   sigemptyset(&action.sa_mask);
   sigaction(SIGINFO, &action, NULL);
 #endif /* SIGINFO */
