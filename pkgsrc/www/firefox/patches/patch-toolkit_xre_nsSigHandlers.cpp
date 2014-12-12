$NetBSD$

--- toolkit/xre/nsSigHandlers.cpp.orig	2013-06-18 11:01:44.000000000 +0000
+++ toolkit/xre/nsSigHandlers.cpp
@@ -240,7 +240,13 @@ void InstallSignalHandlers(const char *P
 #ifdef SA_SIGINFO
   /* Install a handler for floating point exceptions and disable them if they occur. */
   struct sigaction sa, osa;
-  sa.sa_flags = SA_ONSTACK | SA_RESTART | SA_SIGINFO;
+  sa.sa_flags = SA_SIGINFO;
+#ifdef SA_ONSTACK
+  sa.sa_flags |= SA_ONSTACK;
+#endif
+#ifdef SA_RESTART
+  sa.sa_flags |= SA_RESTART;
+#endif
   sa.sa_sigaction = fpehandler;
   sigemptyset(&sa.sa_mask);
   sigaction(SIGFPE, &sa, &osa);
