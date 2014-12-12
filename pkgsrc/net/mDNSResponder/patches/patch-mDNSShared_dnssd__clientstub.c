$NetBSD$

--- mDNSShared/dnssd_clientstub.c.orig	2010-06-17 00:06:28.000000000 +0000
+++ mDNSShared/dnssd_clientstub.c
@@ -71,7 +71,11 @@
 		}
 #else
 
+#ifndef __QNXNTO__
 	#include <sys/fcntl.h>		// For O_RDWR etc.
+#else
+	#include <fcntl.h>
+#endif
 	#include <sys/time.h>
 	#include <sys/socket.h>
 	#include <syslog.h>
