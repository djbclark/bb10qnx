$NetBSD$

--- security/coreconf/QNX.mk.orig	2009-09-03 04:57:00.000000000 +0000
+++ nss/coreconf/QNX.mk
@@ -43,11 +43,11 @@ ifeq ($(USE_PTHREADS),1)
 	IMPL_STRATEGY = _PTH
 endif
 
-CC			= qcc
-CCC			= qcc
+CC			= gcc
+CCC			= g++
 RANLIB			= ranlib
 
-DEFAULT_COMPILER = qcc
+DEFAULT_COMPILER = gcc
 ifeq ($(OS_TEST),mips)
 	CPU_ARCH	= mips
 else
@@ -59,7 +59,7 @@ ifdef BUILD_OPT
 	OPTIMIZER	= -O2
 endif
 
-OS_CFLAGS		= $(DSO_CFLAGS) $(OS_REL_CFLAGS) -Vgcc_ntox86 -Wall -pipe -DNTO -DHAVE_STRERROR -D_QNX_SOURCE -D_POSIX_C_SOURCE=199506 -D_XOPEN_SOURCE=500
+OS_CFLAGS		= $(DSO_CFLAGS) $(OS_REL_CFLAGS) -Wall -DNTO -DHAVE_STRERROR -D_QNX_SOURCE -D_POSIX_C_SOURCE=199506 -D_XOPEN_SOURCE=500
 
 ifdef USE_PTHREADS
 	DEFINES		+= -D_REENTRANT
@@ -67,5 +67,5 @@ endif
 
 ARCH			= QNX
 
-DSO_CFLAGS		= -Wc,-fPIC
+DSO_CFLAGS		= -fPIC
 DSO_LDOPTS		= -shared
