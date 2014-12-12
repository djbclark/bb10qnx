$NetBSD$

--- epan/plugins.c.orig	2013-04-22 18:05:19.000000000 +0000
+++ epan/plugins.c
@@ -153,7 +153,7 @@ plugins_scan_dir(const char *dirname)
     void         (*register_codec_module)(void);
 
     gchar         *dot;
-    int            cr;
+    int            cr, flags;
 
     if ((dir = ws_dir_open(dirname, 0, NULL)) != NULL)
     {
@@ -172,7 +172,11 @@ plugins_scan_dir(const char *dirname)
 
             g_snprintf(filename, FILENAME_LEN, "%s" G_DIR_SEPARATOR_S "%s",
                        dirname, name);
-            if ((handle = g_module_open(filename, (GModuleFlags)0)) == NULL)
+	    flags = 0;
+#ifdef __QNXNTO__
+	    flags |= G_MODULE_BIND_LOCAL;
+#endif
+            if ((handle = g_module_open(filename, (GModuleFlags)flags)) == NULL)
             {
                 report_failure("Couldn't load module %s: %s", filename,
                                g_module_error());
