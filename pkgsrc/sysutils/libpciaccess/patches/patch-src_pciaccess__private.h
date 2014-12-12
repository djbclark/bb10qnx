$NetBSD$

--- src/pciaccess_private.h.orig	2012-04-09 17:02:57.000000000 +0000
+++ src/pciaccess_private.h
@@ -42,7 +42,11 @@
  * know of any OS we support where this isn't available in a sufficiently
  * new version, so warn unconditionally.
  */
+#ifndef __QNXNTO__
 #include <sys/fcntl.h>
+#else
+#include <fcntl.h>
+#endif
 
 #ifndef O_CLOEXEC
 #warning O_CLOEXEC not available, please upgrade.
@@ -182,6 +186,7 @@ extern struct pci_system * pci_sys;
 extern int pci_system_linux_sysfs_create( void );
 extern int pci_system_freebsd_create( void );
 extern int pci_system_netbsd_create( void );
+extern int pci_system_nto_create( void );
 extern int pci_system_openbsd_create( void );
 extern void pci_system_openbsd_init_dev_mem( int );
 extern int pci_system_solx_devfs_create( void );
