$NetBSD: patch-include_drm_drm.h,v 1.1 2012/08/13 09:05:07 wiz Exp $

Fix compilation on systems that don't provide O_CLOEXEC.

--- include/drm/drm.h.orig	2012-10-05 15:50:58.000000000 +0000
+++ include/drm/drm.h
@@ -48,6 +48,7 @@ typedef unsigned int drm_handle_t;
 #include <sys/ioccom.h>
 #else
 #include <sys/ioctl.h>
+#include <inttypes.h>
 #endif
 #include <sys/types.h>
 typedef int8_t   __s8;
@@ -622,7 +623,11 @@ struct drm_get_cap {
 	__u64 value;
 };
 
+#ifdef O_CLOEXEC
 #define DRM_CLOEXEC O_CLOEXEC
+#else
+#define DRM_CLOEXEC 0
+#endif
 struct drm_prime_handle {
 	__u32 handle;
 
