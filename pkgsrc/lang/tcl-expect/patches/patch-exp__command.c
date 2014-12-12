$NetBSD$

--- exp_command.c.orig	2010-07-01 00:53:49.000000000 +0000
+++ exp_command.c
@@ -1201,7 +1201,7 @@ Exp_SpawnObjCmd(
     /* according to Stevens - Adv. Prog..., p 642 */
     /* Oops, it appears that the CIBAUD is on Linux also */
     /* so let's try without... */
-#ifdef __QNX__
+#if defined(__QNX__) && !defined(__QNXNTO__)
     if (tcsetct(0, getpid()) == -1) {
 	restore_error_fd
 	    expErrorLog("failed to get controlling terminal using TIOCSCTTY");
