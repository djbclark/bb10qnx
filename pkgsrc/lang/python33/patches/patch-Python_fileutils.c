$NetBSD$

--- Python/fileutils.c.orig	2013-05-15 16:33:00.000000000 +0000
+++ Python/fileutils.c
@@ -4,8 +4,8 @@
 #  include <windows.h>
 #endif
 
-#ifdef HAVE_LANGINFO_H
 #include <locale.h>
+#ifdef HAVE_LANGINFO_H
 #include <langinfo.h>
 #endif
 
