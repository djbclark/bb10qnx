$NetBSD$

--- avahi-daemon/main.c.orig	2010-11-18 03:00:26.000000000 +0000
+++ avahi-daemon/main.c
@@ -1078,7 +1078,9 @@ static void ignore_signal(int sig)  {
 
     memset(&sa, 0, sizeof(sa));
     sa.sa_handler = SIG_IGN;
+#ifdef SA_RESTART
     sa.sa_flags = SA_RESTART;
+#endif
 
     sigaction(sig, &sa, NULL);
 }
