$NetBSD$

--- glib/libcharset/localcharset.c.orig	2011-08-16 00:51:30.000000000 +0000
+++ glib/libcharset/localcharset.c
@@ -362,6 +362,11 @@ _g_locale_charset_raw (void)
 	}
     }
 
+#ifdef __QNXNTO__ /* We need nl_langinfo() */
+  if (locale != NULL && strcmp(locale, "C") == 0)
+         locale = "ASCII";
+#endif
+
   /* On some old systems, one used to set locale = "iso8859_1". On others,
      you set it to "language_COUNTRY.charset". In any case, we resolve it
      through the charset.alias file.  */
