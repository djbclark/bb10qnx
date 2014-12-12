$NetBSD$

--- Modules/mmapmodule.c.orig	2011-06-11 15:46:27.000000000 +0000
+++ Modules/mmapmodule.c
@@ -23,7 +23,7 @@
 
 #ifndef MS_WINDOWS
 #define UNIX
-# ifdef __APPLE__
+# if defined(__APPLE__) || defined(__QNXNTO__)
 #  include <fcntl.h>
 # endif
 #endif
