$NetBSD$

--- mkdtemp.c.orig	2009-04-30 17:33:48.000000000 +0000
+++ mkdtemp.c
@@ -10,8 +10,8 @@
 char *mkdtemp (char *tmpl)
 {
     static const char LETTERS[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
-    static long       value = 0;
-    long              v;
+    static unsigned long       value = 0;
+    unsigned long              v;
     int               len;
     int               i, j;
 
@@ -22,7 +22,7 @@ char *mkdtemp (char *tmpl)
         return NULL;
     }
 
-    value += ((long) time (NULL)) ^ getpid ();
+    value += ((unsigned long) time (NULL)) ^ getpid ();
 
     for (i = 0; i < 7 ; ++i, value += 7777)
     {
