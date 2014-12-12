$NetBSD: patch-dom_plugins_ipc_PluginModuleChild.h,v 1.1 2013/07/17 11:00:13 jperkin Exp $

--- dom/plugins/ipc/PluginModuleChild.h.orig	2013-06-18 11:01:17.000000000 +0000
+++ dom/plugins/ipc/PluginModuleChild.h
@@ -325,7 +325,7 @@ private:
 
     // we get this from the plugin
     NP_PLUGINSHUTDOWN mShutdownFunc;
-#if defined(OS_LINUX) || defined(OS_BSD)
+#if defined(OS_LINUX) || defined(OS_BSD) || defined(OS_SOLARIS) || defined(OS_QNX)
     NP_PLUGINUNIXINIT mInitializeFunc;
 #elif defined(OS_WIN) || defined(OS_MACOSX)
     NP_PLUGININIT mInitializeFunc;
