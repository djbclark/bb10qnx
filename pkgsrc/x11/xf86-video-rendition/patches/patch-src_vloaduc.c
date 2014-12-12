$NetBSD$

--- src/vloaduc.c.orig	2012-06-06 11:37:36.000000000 +0000
+++ src/vloaduc.c
@@ -20,6 +20,9 @@
 #ifdef HAVE_ELF_H
 #include <elf.h>
 #endif
+#ifdef __QNXNTO__
+#include <sys/elf.h>
+#endif
 #ifdef HAVE_ELF_ABI_H
 #include <elf_abi.h>
 #endif
