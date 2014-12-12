$NetBSD$

--- xinit.c.orig	2011-10-20 05:47:36.000000000 +0000
+++ xinit.c
@@ -279,7 +279,9 @@ main(int argc, char *argv[])
     memset(&si, 0, sizeof(si));
     si.sa_handler = sigIgnore;
     sigemptyset(&si.sa_mask);
+#ifdef SA_RESTART
     si.sa_flags = SA_RESTART;
+#endif
 
     sigaction(SIGALRM, &si, NULL);
     sigaction(SIGUSR1, &si, NULL);
