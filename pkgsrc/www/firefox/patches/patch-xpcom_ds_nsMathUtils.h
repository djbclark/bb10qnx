$NetBSD$

--- xpcom/ds/nsMathUtils.h.orig	2013-06-18 11:01:44.000000000 +0000
+++ xpcom/ds/nsMathUtils.h
@@ -98,7 +98,7 @@ inline NS_HIDDEN_(bool) NS_finite(double
 #ifdef WIN32
     // NOTE: '!!' casts an int to bool without spamming MSVC warning C4800.
     return !!_finite(d);
-#elif defined(XP_DARWIN)
+#elif defined(XP_DARWIN) || defined(__QNXNTO__)
     // Darwin has deprecated |finite| and recommends |isfinite|. The former is
     // not present in the iOS SDK.
     return std::isfinite(d);
