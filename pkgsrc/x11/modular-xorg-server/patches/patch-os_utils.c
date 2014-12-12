$NetBSD$

--- os/utils.c.orig	2012-08-19 15:39:28.000000000 +0000
+++ os/utils.c
@@ -318,7 +318,13 @@ LockServer(void)
             /*
              * Read the pid from the existing file
              */
-            lfd = open(LockFile, O_RDONLY | O_NOFOLLOW);
+            int oflags;
+
+            oflags = O_RDONLY;
+#ifdef O_NOFOLLOW
+            oflags |= O_NOFOLLOW;
+#endif
+            lfd = open(LockFile, oflags);
             if (lfd < 0) {
                 unlink(tmp);
                 FatalError("Can't read lock file %s\n", LockFile);
