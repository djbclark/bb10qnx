$NetBSD$

--- include/my_global.h.orig	2011-02-11 19:20:21.000000000 +0000
+++ include/my_global.h
@@ -506,6 +506,7 @@ extern "C" int madvise(void *addr, size_
 #endif
 
 #ifdef __QNXNTO__
+#include <sys/neutrino.h>
 /* This has to be after include limits.h */
 #define HAVE_ERRNO_AS_DEFINE
 #define HAVE_FCNTL_LOCK
@@ -515,9 +516,14 @@ extern "C" int madvise(void *addr, size_
 #ifdef __cplusplus
 #ifndef HAVE_RINT
 #define HAVE_RINT
-#endif                          /* rint() and isnan() functions are not */
-#define rint(a) std::rint(a)    /* visible in C++ scope due to an error */
-#define isnan(a) std::isnan(a)  /* in the usr/include/math.h on QNX     */
+#endif                          
+#if !defined(_NTO_VERSION) || (_NTO_VERSION - 0 < 650)
+/* rint() and isnan() functions are not   */
+/* visible in C++ scope due to an error   */
+/* in the usr/include/math.h on early QNX */
+#define rint(a) std::rint(a)    
+#define isnan(a) std::isnan(a)  
+#endif
 #endif
 #endif
 
