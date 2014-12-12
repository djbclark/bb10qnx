$NetBSD$

--- include/private/gcconfig.h.orig	2012-05-11 17:09:00.000000000 +0000
+++ include/private/gcconfig.h
@@ -371,6 +371,10 @@
 #    define X86_64
 #    define mach_type_known
 # endif
+# if defined(__QNXNTO__) && (defined(__X86__))
+#   define I386
+#   define mach_type_known
+# endif
 # if defined(FREEBSD) && defined(__sparc__)
 #    define SPARC
 #    define mach_type_known
@@ -1441,6 +1445,17 @@
       /* This should be looked into some more.                          */
 #     define NO_PTHREAD_TRYLOCK
 #   endif /* DARWIN */
+#   ifdef __QNXNTO__
+#       include <sys/storage.h>
+#       include <inttypes.h>
+#       include <sys/mman.h>
+#       ifndef ROUNDOUP
+#            define ROUNDUP(x, m)  (((x) + (m) - 1) & ~((m) - 1))
+#       endif
+#       define STACKBOTTOM ROUNDUP((uintptr_t)__tls(), __PAGESIZE)
+        extern int _start[];
+#       define DATASTART (&_start)
+#   endif
 # endif
 
 # ifdef NS32K
