$NetBSD$

--- appl/telnet/telnetd/sys_term.c.orig	2010-09-13 07:23:34.000000000 +0000
+++ appl/telnet/telnetd/sys_term.c
@@ -129,6 +129,9 @@ char	wtmpf[]	= "/etc/wtmp";
 #ifdef HAVE_LIBUTIL_H
 #include <libutil.h>
 #endif
+#ifdef __QNXNTO__
+#include <unix.h> /* openpty */
+#endif
 
 # ifndef	TCSANOW
 #  ifdef TCSETS
@@ -1011,7 +1014,7 @@ int cleanopen(char *line)
     return(t);
 }
 
-#if !defined(BSD4_4)
+#if !defined(BSD4_4) && !defined(__QNXNTO__)
 
 int login_tty(int t)
 {
