$NetBSD$

--- src/tests.c.orig	2012-04-12 20:05:11.000000000 +0000
+++ src/tests.c
@@ -440,7 +440,11 @@ test_bye (gnutls_session_t session)
     return TEST_FAILED;
 
 #ifndef _WIN32
+#ifndef __QNXNTO__
   old = siginterrupt (SIGALRM, 1);
+#else
+  /* interrupt is the default */
+#endif
   alarm (secs);
 #else
   setsockopt ((int) gnutls_transport_get_ptr (session), SOL_SOCKET,
@@ -454,7 +458,9 @@ test_bye (gnutls_session_t session)
   while (ret > 0);
 
 #ifndef _WIN32
+#ifndef __QNXNTO__
   siginterrupt (SIGALRM, old);
+#endif
 #else
   if (WSAGetLastError () == WSAETIMEDOUT ||
       WSAGetLastError () == WSAECONNABORTED)
