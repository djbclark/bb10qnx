$NetBSD: patch-dom_plugins_ipc_PluginModuleChild.cpp,v 1.1 2013/07/17 11:00:13 jperkin Exp $

--- dom/plugins/ipc/PluginModuleChild.cpp.orig	2013-06-18 11:01:17.000000000 +0000
+++ dom/plugins/ipc/PluginModuleChild.cpp
@@ -201,7 +201,7 @@ PluginModuleChild::Init(const std::strin
 
     // TODO: use PluginPRLibrary here
 
-#if defined(OS_LINUX) || defined(OS_BSD)
+#if defined(OS_LINUX) || defined(OS_BSD) || defined(OS_SOLARIS) || defined(OS_QNX)
     mShutdownFunc =
         (NP_PLUGINSHUTDOWN) PR_FindFunctionSymbol(mLibrary, "NP_Shutdown");
 
@@ -1836,7 +1836,7 @@ PluginModuleChild::AnswerNP_GetEntryPoin
     PLUGIN_LOG_DEBUG_METHOD;
     AssertPluginThread();
 
-#if defined(OS_LINUX) || defined(OS_BSD)
+#if defined(OS_LINUX) || defined(OS_BSD) || defined(OS_SOLARIS) || defined(OS_QNX)
     return true;
 #elif defined(OS_WIN) || defined(OS_MACOSX)
     *_retval = mGetEntryPointsFunc(&mFunctions);
@@ -1865,7 +1865,7 @@ PluginModuleChild::AnswerNP_Initialize(c
     SendBackUpXResources(FileDescriptor(xSocketFd));
 #endif
 
-#if defined(OS_LINUX) || defined(OS_BSD)
+#if defined(OS_LINUX) || defined(OS_BSD) || defined(OS_SOLARIS) || defined(OS_QNX)
     *_retval = mInitializeFunc(&sBrowserFuncs, &mFunctions);
     return true;
 #elif defined(OS_WIN) || defined(OS_MACOSX)
