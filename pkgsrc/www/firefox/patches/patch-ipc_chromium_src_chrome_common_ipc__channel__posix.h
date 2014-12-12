$NetBSD$

--- ipc/chromium/src/chrome/common/ipc_channel_posix.h.orig	2013-06-18 11:01:23.000000000 +0000
+++ ipc/chromium/src/chrome/common/ipc_channel_posix.h
@@ -95,7 +95,7 @@ class Channel::ChannelImpl : public Mess
   };
 
   // This is a control message buffer large enough to hold kMaxReadFDs
-#if defined(OS_MACOSX) || defined(OS_NETBSD)
+#if defined(OS_MACOSX) || defined(OS_NETBSD) || defined(OS_QNX)
   // TODO(agl): OSX appears to have non-constant CMSG macros!
   char input_cmsg_buf_[1024];
 #else
