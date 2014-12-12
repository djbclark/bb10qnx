$NetBSD$

--- libcharset/lib/localcharset.c.orig	2011-02-28 22:43:35.000000000 +0000
+++ libcharset/lib/localcharset.c
@@ -446,6 +446,10 @@ locale_charset (void)
             locale = getenv ("LANG");
         }
     }
+#ifdef __QNXNTO__ /* We need nl_langinfo() */
+  if (locale != NULL && strcmp(locale, "C") == 0)
+	  locale = "ASCII";
+#endif
 
   /* On some old systems, one used to set locale = "iso8859_1". On others,
      you set it to "language_COUNTRY.charset". In any case, we resolve it
