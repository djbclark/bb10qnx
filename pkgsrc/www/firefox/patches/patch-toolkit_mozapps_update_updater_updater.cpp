$NetBSD$

--- toolkit/mozapps/update/updater/updater.cpp.orig	2013-06-18 11:01:43.000000000 +0000
+++ toolkit/mozapps/update/updater/updater.cpp
@@ -47,6 +47,9 @@
 #include <fcntl.h>
 #include <limits.h>
 #include <errno.h>
+#ifdef __QNXNTO__
+#include <unix.h>
+#endif
 
 #include "updatelogging.h"
 
@@ -3275,7 +3278,7 @@ int add_dir_entries(const NS_tchar *dirp
   return rv;
 }
 
-#elif defined(SOLARIS)
+#elif defined(SOLARIS) || defined(__QNXNTO__)
 int add_dir_entries(const NS_tchar *dirpath, ActionList *list)
 {
   int rv = OK;
