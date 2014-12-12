$NetBSD$

--- lib/vfs/mc-vfs/cpio.c.orig	2010-11-08 11:46:13.000000000 +0000
+++ lib/vfs/mc-vfs/cpio.c
@@ -576,13 +576,21 @@ cpio_read_crc_head (struct vfs_class *me
 	return STATUS_TRAIL;
     }
 
+#ifndef __QNXNTO__
     u.st.st_dev = makedev (hd.c_dev, hd.c_devmin);
+#else
+    u.st.st_dev = makedev (hd.c_dev, hd.c_devmin, 0);
+#endif
     u.st.st_ino = hd.c_ino;
     u.st.st_mode = hd.c_mode;
     u.st.st_nlink = hd.c_nlink;
     u.st.st_uid = hd.c_uid;
     u.st.st_gid = hd.c_gid;
+#ifndef __QNXNTO__
     u.st.st_rdev = makedev (hd.c_rdev, hd.c_rdevmin);
+#else
+    u.st.st_rdev = makedev (hd.c_rdev, hd.c_rdevmin, 0);
+#endif
     u.st.st_size = hd.c_filesize;
     u.st.st_atime = u.st.st_mtime = u.st.st_ctime = hd.c_mtime;
 
