$NetBSD: patch-js_src_vm_Stack.cpp,v 1.1 2013/07/17 11:00:13 jperkin Exp $

--- js/src/vm/Stack.cpp.orig	2013-06-18 11:01:27.000000000 +0000
+++ js/src/vm/Stack.cpp
@@ -807,7 +807,14 @@ StackSpace::sizeOf()
 #endif
 
     MincoreArgType *vec = (MincoreArgType *) js_malloc(numPages);
+#ifdef __sun
+    int result = mincore((caddr_t)base_, numBytes, vec);
+#elif defined(__QNXNTO__)
+    int result = 0;
+    memset(vec, 0xff, numPages);
+#else
     int result = mincore(base_, numBytes, vec);
+#endif
     if (result) {
         js_free(vec);
         /*
