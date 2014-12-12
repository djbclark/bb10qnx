$NetBSD$

--- hints/qnx.sh.orig	2013-03-04 15:16:22.000000000 +0000
+++ hints/qnx.sh
@@ -265,4 +265,27 @@ else
   # Some routines are only in our static libc.
   # eg crypt() getlogin() getlogin_r()
   usenm=false
+
+  loclibpth="/usr/local/lib ${prefix}/lib"
+
+  d_getprotoent_r="$undef"
+  d_getprotobyname_r="$undef"
+  d_getprotobynumber_r="$undef"
+  d_setprotoent_r="$undef"
+  d_endprotoent_r="$undef"
+  d_getservent_r="$undef"
+  d_getservbyname_r="$undef"
+  d_getservbyport_r="$undef"
+  d_setservent_r="$undef"
+  d_endservent_r="$undef"
+  d_getprotoent_r_proto="0"
+  d_getprotobyname_r_proto="0"
+  d_getprotobynumber_r_proto="0"
+  d_setprotoent_r_proto="0"
+  d_endprotoent_r_proto="0"
+  d_getservent_r_proto="0"
+  d_getservbyname_r_proto="0"
+  d_getservbyport_r_proto="0"
+  d_setservent_r_proto="0"
+  d_endservent_r_proto="0"
 fi
