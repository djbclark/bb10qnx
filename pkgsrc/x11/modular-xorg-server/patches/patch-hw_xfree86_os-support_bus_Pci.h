$NetBSD$

--- hw/xfree86/os-support/bus/Pci.h.orig	2012-05-17 17:09:03.000000000 +0000
+++ hw/xfree86/os-support/bus/Pci.h
@@ -139,7 +139,7 @@
 #define osPciInit(x) do {} while (0)
 #elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__) || \
 	defined(__OpenBSD__) || defined(__NetBSD__) || \
-	defined(__DragonFly__) || defined(__sun) || defined(__GNU__)
+	defined(__DragonFly__) || defined(__sun) || defined(__GNU__) || defined(__QNXNTO__)
 extern void osPciInit(void);
 #else
 #error No PCI support available for this architecture/OS combination
