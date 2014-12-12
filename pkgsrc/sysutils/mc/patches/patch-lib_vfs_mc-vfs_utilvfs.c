$NetBSD$

--- lib/vfs/mc-vfs/utilvfs.c.orig	2010-11-08 11:46:13.000000000 +0000
+++ lib/vfs/mc-vfs/utilvfs.c
@@ -717,7 +717,11 @@ vfs_parse_ls_lga (const char *p, struct 
 		goto error;
 	}
 #ifdef HAVE_STRUCT_STAT_ST_RDEV
+#ifndef __QNXNTO__
 	s->st_rdev = makedev (maj, min);
+#else
+	s->st_rdev = makedev (maj, min, 0);
+#endif
 #endif
 	s->st_size = 0;
 
