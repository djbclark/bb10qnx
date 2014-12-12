$NetBSD$

--- Modules/_ctypes/ctypes.h.orig	2011-06-11 15:46:26.000000000 +0000
+++ Modules/_ctypes/ctypes.h
@@ -32,8 +32,12 @@ typedef Py_ssize_t (*charbufferproc)(PyO
 
 
 #ifndef MS_WIN32
+#ifndef max
 #define max(a, b) ((a) > (b) ? (a) : (b))
+#endif
+#ifndef min
 #define min(a, b) ((a) < (b) ? (a) : (b))
+#endif
 
 #define PARAMFLAG_FIN 0x1
 #define PARAMFLAG_FOUT 0x2
