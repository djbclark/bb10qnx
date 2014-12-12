$NetBSD$

--- src/editline/readline.h.orig	2013-06-01 15:46:07.000000000 +0000
+++ src/editline/readline.h
@@ -75,7 +75,7 @@ typedef KEYMAP_ENTRY *Keymap;
 
 #ifndef CTRL
 #include <sys/ioctl.h>
-#if !defined(__sun) && !defined(__hpux) && !defined(_AIX)
+#if !defined(__sun) && !defined(__hpux) && !defined(_AIX) && !defined(__QNXNTO__)
 #include <sys/ttydefaults.h>
 #endif
 #ifndef CTRL
