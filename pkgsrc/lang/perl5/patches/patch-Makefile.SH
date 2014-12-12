$NetBSD$

--- Makefile.SH.orig	2011-06-17 00:06:09.000000000 +0000
+++ Makefile.SH
@@ -67,7 +67,7 @@ true)
 	sunos*)
 		linklibperl="-lperl"
 		;;
-	netbsd*|freebsd[234]*|openbsd*|dragonfly*)
+	netbsd*|freebsd[234]*|openbsd*|dragonfly*|qnx*|nto*)
 		linklibperl="-L. -lperl"
 		;;
 	interix*)
