$NetBSD$

--- avahi-utils/sigint.c.orig	2010-08-26 00:51:39.000000000 +0000
+++ avahi-utils/sigint.c
@@ -97,7 +97,9 @@ int sigint_install(AvahiSimplePoll *spol
 
     memset(&sa, 0, sizeof(sa));
     sa.sa_handler = handler;
+#ifdef SA_RESTART
     sa.sa_flags = SA_RESTART;
+#endif
 
     if (sigaction(SIGINT, &sa, &old_sigint_sa) < 0) {
         fprintf(stderr, "sigaction() failed: %s\n", strerror(errno));
