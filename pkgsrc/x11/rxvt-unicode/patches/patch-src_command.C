$NetBSD$

--- src/command.C.orig	2012-11-30 07:06:26.000000000 +0000
+++ src/command.C
@@ -61,6 +61,9 @@
 #if LINUX_YIELD_HACK
 # include <time.h>
 #endif
+#ifdef __QNXNTO__
+# include <wctype.h>
+#endif
 
 /*----------------------------------------------------------------------*/
 
@@ -205,7 +208,17 @@ rxvt_term::iso14755_51 (unicode_t ch, re
     {
       rxvt_font *f = (*fs)[fs->find_font_idx (chr[i])];
       fname[i] = rxvt_utf8towcs (f->name);
+#ifndef __QNXNTO__
       max_it (width, wcswidth (fname[i], wcslen (fname[i])));
+#else
+      int  j, lim, curwidth;
+      lim = wcslen(fname[i]);
+      for (j = 0, curwidth = 0; j < lim; j++) {
+        if (iswprint(fname[i][j]))
+          curwidth++;
+      }
+      max_it (width, curwidth);
+#endif
     }
 
   max_it (width, strlen (attr));
