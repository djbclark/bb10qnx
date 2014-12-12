$NetBSD$

--- dbm/include/cdefs.h.orig	2013-06-18 11:01:16.000000000 +0000
+++ dbm/include/cdefs.h
@@ -42,9 +42,13 @@
 #define	__BEGIN_DECLS	extern "C" {
 #define	__END_DECLS	}
 #else
+#ifndef __BEGIN_DECLS
 #define	__BEGIN_DECLS
+#endif
+#ifndef __END_DECLS
 #define	__END_DECLS
 #endif
+#endif
 
 /*
  * The __CONCAT macro is used to concatenate parts of symbol names, e.g.
@@ -113,9 +117,11 @@
 #define	__attribute__(x)	/* delete __attribute__ if non-gcc or gcc1 */
 #if defined(__GNUC__) && !defined(__STRICT_ANSI__)
 #define	__dead		__volatile
+#ifndef __pure
 #define	__pure		__const
 #endif
 #endif
+#endif
 
 /* Delete pseudo-keywords wherever they are not available or needed. */
 #ifndef __dead
