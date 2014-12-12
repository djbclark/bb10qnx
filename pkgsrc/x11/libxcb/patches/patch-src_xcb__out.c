$NetBSD$

--- src/xcb_out.c.orig	2012-01-11 17:01:29.000000000 +0000
+++ src/xcb_out.c
@@ -334,6 +334,7 @@ int _xcb_out_init(_xcb_out *out)
 
 void _xcb_out_destroy(_xcb_out *out)
 {
+    pthread_cond_destroy(&out->socket_cond);
     pthread_cond_destroy(&out->cond);
     pthread_mutex_destroy(&out->reqlenlock);
 }
