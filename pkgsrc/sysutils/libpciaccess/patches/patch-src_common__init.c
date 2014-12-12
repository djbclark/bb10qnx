$NetBSD$

--- src/common_init.c.orig	2012-04-09 17:02:57.000000000 +0000
+++ src/common_init.c
@@ -64,6 +64,8 @@ pci_system_init( void )
     err = pci_system_solx_devfs_create();
 #elif defined(__GNU__)
     err = pci_system_x86_create();
+#elif defined(__QNXNTO__)
+    err = pci_system_nto_create();
 #endif
 
     return err;
