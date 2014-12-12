$NetBSD$

--- exp_clib.c.orig	2010-08-31 22:20:27.000000000 +0000
+++ exp_clib.c
@@ -2082,7 +2082,7 @@ when trapping, see below in child half o
 #if defined(TIOCSCTTY) && !defined(sun) && !defined(hpux)
 	/* 4.3+BSD way to acquire controlling terminal */
 	/* according to Stevens - Adv. Prog..., p 642 */
-#ifdef __QNX__ /* posix in general */
+#if defined(__QNX__) && !defined(__QNXNTO__) /* posix in general */
 	if (tcsetct(0, getpid()) == -1) {
 	  restore_error_fd
 	  expErrorLog("failed to get controlling terminal using TIOCSCTTY");
