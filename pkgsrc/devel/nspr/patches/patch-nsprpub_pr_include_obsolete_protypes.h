$NetBSD$

--- nsprpub/pr/include/obsolete/protypes.h.orig	2012-03-06 13:13:55.000000000 +0000
+++ nspr/pr/include/obsolete/protypes.h
@@ -73,7 +73,7 @@ typedef PRUint64 uint64;
  */
 
 #if !defined(XP_BEOS)
-#if !defined(_WIN32) && !defined(XP_OS2) && !defined(NTO)
+#if !defined(_WIN32) && !defined(XP_OS2)
 typedef PRUint32 uint32;
 #else
 typedef unsigned long uint32;
@@ -110,7 +110,7 @@ typedef PRInt64 int64;
 
 #if !defined(XP_BEOS) && !defined(_PR_AIX_HAVE_BSD_INT_TYPES) \
     && !defined(HPUX)
-#if !defined(_WIN32) && !defined(XP_OS2) && !defined(NTO)
+#if !defined(_WIN32) && !defined(XP_OS2)
 typedef PRInt32 int32;
 #else
 typedef long int32;
