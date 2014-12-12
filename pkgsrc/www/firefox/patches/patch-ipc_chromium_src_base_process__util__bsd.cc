$NetBSD$

--- ipc/chromium/src/base/process_util_bsd.cc.orig	2013-06-18 11:01:23.000000000 +0000
+++ ipc/chromium/src/base/process_util_bsd.cc
@@ -4,6 +4,9 @@
 
 // derived from process_util_linux.cc and process_util_mac.cc
 
+#ifdef __QNXNTO__
+#define __STDC_CONSTANT_MACROS
+#endif
 #include "base/process_util.h"
 
 #include <sys/param.h>
@@ -314,6 +317,7 @@ void SetCurrentProcessPrivileges(ChildPr
 NamedProcessIterator::NamedProcessIterator(const std::wstring& executable_name,
                                            const ProcessFilter* filter)
 {
+#if !defined(OS_QNX)
   int numEntries;
   kvm_t *kvm;
   std::string exe(WideToASCII(executable_name));
@@ -361,6 +365,9 @@ NamedProcessIterator::NamedProcessIterat
   }
   nextEntry = 0;
   kvm_close(kvm);
+#else
+  nextEntry = 0;
+#endif
 }
 
 NamedProcessIterator::~NamedProcessIterator() {
