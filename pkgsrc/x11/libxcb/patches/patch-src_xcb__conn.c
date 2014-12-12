$NetBSD$

--- src/xcb_conn.c.orig	2012-09-25 10:31:53.000000000 +0000
+++ src/xcb_conn.c
@@ -443,8 +443,12 @@ int _xcb_conn_wait(xcb_connection_t *c, 
          */
         int may_read = c->in.reading == 1 || !count;
 #if USE_POLL
+#ifndef __QNXNTO__
         if(may_read && (fd.revents & POLLIN) == POLLIN)
 #else
+        if(may_read && (fd.revents & POLLIN) != 0)
+#endif
+#else
         if(may_read && FD_ISSET(c->fd, &rfds))
 #endif
             ret = ret && _xcb_in_read(c);
