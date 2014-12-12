$NetBSD: patch-ipc_chromium_chromium-config.mk,v 1.1 2013/07/17 11:00:13 jperkin Exp $

--- ipc/chromium/chromium-config.mk.orig	2013-06-18 11:01:23.000000000 +0000
+++ ipc/chromium/chromium-config.mk
@@ -105,6 +105,22 @@ DEFINES += \
   $(NULL)
 
 else # } {
+ifeq ($(OS_ARCH),SunOS) # {
+
+OS_SOLARIS = 1
+DEFINES += \
+  -DOS_SOLARIS=1 \
+  $(NULL)
+
+else # } {
+ifeq ($(OS_ARCH),QNX) # {
+
+OS_QNX = 1
+DEFINES += \
+  -DOS_QNX=1 \
+ $(NULL)
+
+else # } {
 
 OS_LINUX = 1
 DEFINES += \
@@ -117,4 +133,6 @@ endif # }
 endif # }
 endif # }
 endif # }
+endif # }
+endif # }
 
