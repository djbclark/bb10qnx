$NetBSD$

--- src/ResConfig.c.orig	2012-03-16 05:52:07.000000000 +0000
+++ src/ResConfig.c
@@ -427,7 +427,16 @@ _get_part (
 	}
 	*buf_ptr = '\0';
 
+#ifndef __QNXNTO__
 	*part = XtNewString (buffer);	/* return a new string to part	*/
+#else
+	/*
+	 * Silence warning which breaks at -Werror=address.  Doesn't seem
+	 * to be needed with gcc > 4.4.2.
+	 */
+	char *tmp = buffer;
+	*part = XtNewString (tmp);	/* return a new string to part	*/
+#endif
 
 	if (strcmp (*indx, "") == 0)
 		*indx = NULL;
