$NetBSD$

--- ffserver.c.orig	2013-01-23 16:52:39.000000000 +0000
+++ ffserver.c
@@ -4700,7 +4700,10 @@ int main(int argc, char **argv)
     av_lfg_init(&random_state, av_get_random_seed());
 
     sigact.sa_handler = handle_child_exit;
-    sigact.sa_flags = SA_NOCLDSTOP | SA_RESTART;
+    sigact.sa_flags = SA_NOCLDSTOP;
+#ifdef SA_RESTART
+    sigact.sa_flags |= SA_RESTART;
+#endif
     sigaction(SIGCHLD, &sigact, 0);
 
     if (parse_ffconfig(config_filename) < 0) {
