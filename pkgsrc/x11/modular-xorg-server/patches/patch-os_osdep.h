$NetBSD$

--- os/osdep.h.orig	2012-05-17 17:09:04.000000000 +0000
+++ os/osdep.h
@@ -72,7 +72,7 @@ SOFTWARE.
 #if defined(NOFILE) && !defined(NOFILES_MAX)
 #define OPEN_MAX NOFILE
 #else
-#if !defined(WIN32)
+#if !defined(WIN32) && !defined(__QNXNTO__)
 #define OPEN_MAX NOFILES_MAX
 #else
 #define OPEN_MAX 256
