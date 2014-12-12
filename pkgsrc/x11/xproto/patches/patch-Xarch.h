$NetBSD$

--- Xarch.h.orig	2012-03-16 06:11:44.000000000 +0000
+++ Xarch.h
@@ -68,6 +68,8 @@
 #   if !defined(BYTE_ORDER) && defined(__BYTE_ORDER)
 #    define BYTE_ORDER __BYTE_ORDER
 #   endif
+#  elif defined(__QNXNTO__)
+#   include <sys/param.h>
 #  endif
 
 #  ifndef BYTE_ORDER
