$NetBSD: patch-ipc_chromium_src_chrome_common_transport__dib.h,v 1.1 2013/07/17 11:00:13 jperkin Exp $

--- ipc/chromium/src/chrome/common/transport_dib.h.orig	2013-06-18 11:01:23.000000000 +0000
+++ ipc/chromium/src/chrome/common/transport_dib.h
@@ -7,7 +7,7 @@
 
 #include "base/basictypes.h"
 
-#if defined(OS_WIN) || defined(OS_MACOSX) || defined(OS_BSD)
+#if defined(OS_WIN) || defined(OS_MACOSX) || defined(OS_BSD) || defined(OS_QNX)
 #include "base/shared_memory.h"
 #endif
 
@@ -66,11 +66,11 @@ class TransportDIB {
     uint32_t sequence_num;
   };
   typedef HandleAndSequenceNum Id;
-#elif defined(OS_MACOSX) || defined(OS_BSD)
+#elif defined(OS_MACOSX) || defined(OS_BSD) || defined(OS_QNX)
   typedef base::SharedMemoryHandle Handle;
   // On Mac, the inode number of the backing file is used as an id.
   typedef base::SharedMemoryId Id;
-#elif defined(OS_LINUX)
+#elif defined(OS_LINUX) || defined(OS_SOLARIS)
   typedef int Handle;  // These two ints are SysV IPC shared memory keys
   typedef int Id;
 #endif
@@ -108,7 +108,7 @@ class TransportDIB {
 
  private:
   TransportDIB();
-#if defined(OS_WIN) || defined(OS_MACOSX) || defined(OS_BSD)
+#if defined(OS_WIN) || defined(OS_MACOSX) || defined(OS_BSD) || defined(OS_QNX)
   explicit TransportDIB(base::SharedMemoryHandle dib);
   base::SharedMemory shared_memory_;
 #elif defined(OS_LINUX)
