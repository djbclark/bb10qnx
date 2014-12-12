$NetBSD$

--- server-tools/instance-manager/instance.cc.orig	2011-02-11 19:20:34.000000000 +0000
+++ server-tools/instance-manager/instance.cc
@@ -135,7 +135,7 @@ static bool start_process(Instance_optio
      Here we use spawnv(), which  is a combination of fork() and execv()
      in one call. It returns the pid of newly created process (>0) or -1
   */
-  *pi= spawnv(P_NOWAIT, instance_options->mysqld_path, instance_options->argv);
+  *pi= spawnv(P_NOWAIT, instance_options->mysqld_path.str, instance_options->argv);
 #endif
 
   switch (*pi) {
