$NetBSD$

--- nsprpub/pr/src/misc/prnetdb.c.orig	2013-06-18 11:01:38.000000000 +0000
+++ nsprpub/pr/src/misc/prnetdb.c
@@ -73,7 +73,7 @@ PRLock *_pr_dnsLock = NULL;
         || defined(AIX4_3_PLUS) || (defined(AIX) && defined(_THREAD_SAFE)) \
 	|| (defined(HPUX10_10) && defined(_REENTRANT)) \
         || (defined(HPUX10_20) && defined(_REENTRANT)) \
-        || defined(OPENBSD)
+        || defined(OPENBSD) || defined(NTO)
 #define _PR_HAVE_GETPROTO_R
 #define _PR_HAVE_GETPROTO_R_INT
 #endif
@@ -300,7 +300,7 @@ _pr_QueryNetIfs(void)
 }
 
 #elif (defined(DARWIN) && defined(HAVE_GETIFADDRS)) || defined(FREEBSD) \
-    || defined(NETBSD) || defined(OPENBSD)
+    || defined(NETBSD) || defined(OPENBSD) || defined(NTO)
 
 /*
  * Use the BSD getifaddrs function.
