$NetBSD: patch-js_src_ion_AsmJSSignalHandlers.cpp,v 1.1 2013/06/26 11:32:12 ryoon Exp $

--- js/src/ion/AsmJSSignalHandlers.cpp.orig	2013-06-18 11:01:24.000000000 +0000
+++ js/src/ion/AsmJSSignalHandlers.cpp
@@ -127,6 +127,8 @@ using namespace mozilla;
 # define R13_sig(p) ((p)->uc_mcontext.mc_r13)
 # define R14_sig(p) ((p)->uc_mcontext.mc_r14)
 # define R15_sig(p) ((p)->uc_mcontext.mc_r15)
+#elif defined(__QNXNTO__)
+# define EIP_sig(p) (GET_REGIP(&(p)->uc_mcontext.cpu))
 #elif defined(XP_MACOSX)
 // Mach requires special treatment.
 #else
@@ -268,10 +270,14 @@ LookupHeapAccess(const AsmJSModule &modu
 #  include <sys/ucontext.h> // for ucontext_t, mcontext_t
 # endif
 
+# if defined(__QNXNTO__)
+#  include <ucontext.h> // for ucontext_t, mcontext_t
+# endif
+
 # if defined(JS_CPU_X64)
 #  if defined(__DragonFly__)
 #   include <machine/npx.h> // for union savefpu
-#  elif defined(__FreeBSD__) || defined(__OpenBSD__)
+#  elif defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__NetBSD__)
 #   include <machine/fpu.h> // for struct savefpu/fxsave64
 #  endif
 # endif
