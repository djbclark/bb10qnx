$NetBSD$

--- toolkit/mozapps/update/common/updatedefines.h.orig	2013-06-18 11:01:43.000000000 +0000
+++ toolkit/mozapps/update/common/updatedefines.h
@@ -103,7 +103,7 @@ static int mywcsprintf(WCHAR* dest, size
 # include <sys/wait.h>
 # include <unistd.h>
 
-#ifdef SOLARIS
+#if defined(SOLARIS) || defined(__QNXNTO__)
 # include <sys/stat.h>
 #else
 # include <fts.h>
