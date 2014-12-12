$NetBSD$

--- src/slproc.c.orig	2011-04-11 02:37:07.000000000 +0000
+++ src/slproc.c
@@ -20,7 +20,7 @@ Foundation, Inc., 59 Temple Place - Suit
 USA.
 */
 
-#ifndef _XOPEN_SOURCE
+#if !defined(_XOPEN_SOURCE) && !defined(__QNXNTO__)
 # define _XOPEN_SOURCE
 #endif
 #ifndef _XOPEN_SOURCE_EXTENDED
