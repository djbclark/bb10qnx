$NetBSD$

--- signal.c.orig	2012-02-10 22:17:14.000000000 +0000
+++ signal.c
@@ -250,7 +250,9 @@ _evsig_set_handler(struct event_base *ba
 #ifdef _EVENT_HAVE_SIGACTION
 	memset(&sa, 0, sizeof(sa));
 	sa.sa_handler = handler;
+#ifdef SA_RESTART
 	sa.sa_flags |= SA_RESTART;
+#endif
 	sigfillset(&sa.sa_mask);
 
 	if (sigaction(evsignal, &sa, sig->sh_old[evsignal]) == -1) {
