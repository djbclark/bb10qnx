$NetBSD$

--- lib/vfs/mc-vfs/fish.c.orig	2010-11-08 11:46:13.000000000 +0000
+++ lib/vfs/mc-vfs/fish.c
@@ -745,7 +745,11 @@ fish_dir_load (struct vfs_class *me, str
                 if (sscanf (buffer + 1, "%d,%d", &maj, &min) != 2)
                     break;
 #ifdef HAVE_STRUCT_STAT_ST_RDEV
+#ifndef __QNXNTO__
                 ST.st_rdev = makedev (maj, min);
+#else
+                ST.st_rdev = makedev (maj, min, 0);
+#endif
 #endif
             }
         }
