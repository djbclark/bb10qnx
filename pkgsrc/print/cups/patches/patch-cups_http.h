$NetBSD$

--- cups/http.h.orig	2011-05-21 04:02:41.000000000 +0000
+++ cups/http.h
@@ -88,7 +88,7 @@ extern "C" {
 #if defined(AF_INET6) && !defined(s6_addr32)
 #  if defined(__sun)
 #    define s6_addr32	_S6_un._S6_u32
-#  elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__APPLE__)|| defined(__DragonFly__)
+#  elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__APPLE__)|| defined(__DragonFly__) || defined(__QNXNTO__)
 #    define s6_addr32	__u6_addr.__u6_addr32
 #  elif defined(__osf__)
 #    define s6_addr32	s6_un.sa6_laddr
