$NetBSD$

--- auth-shadow.c.orig	2007-04-29 02:10:58.000000000 +0000
+++ auth-shadow.c
@@ -55,6 +55,7 @@ extern Buffer loginmsg;
 int
 auth_shadow_acctexpired(struct spwd *spw)
 {
+#ifndef	BROKEN_SHADOW_EXPIRE
 	time_t today;
 	int daysleft;
 	char buf[256];
@@ -76,6 +77,7 @@ auth_shadow_acctexpired(struct spwd *spw
 		    daysleft == 1 ? "" : "s");
 		buffer_append(&loginmsg, buf, strlen(buf));
 	}
+#endif
 
 	return 0;
 }
