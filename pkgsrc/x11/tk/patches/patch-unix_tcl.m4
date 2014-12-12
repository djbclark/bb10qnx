$NetBSD$

--- unix/tcl.m4.orig	2013-04-01 18:36:49.000000000 +0000
+++ unix/tcl.m4
@@ -1816,18 +1816,22 @@ AC_DEFUN([SC_CONFIG_CFLAGS], [
 		])
 	    ])
 	    ;;
-	QNX-6*)
+	QNX-[68]*)
 	    # QNX RTP
 	    # This may work for all QNX, but it was only reported for v6.
 	    SHLIB_CFLAGS="-fPIC"
-	    SHLIB_LD="ld -Bshareable -x"
-	    SHLIB_LD_LIBS=""
+	    SHLIB_LD='${CC} -shared ${CFLAGS} ${LDFLAGS}'
+	    SHLIB_LD_LIBS='${LIBS}'
 	    SHLIB_SUFFIX=".so"
 	    DL_OBJS="tclLoadDl.o"
 	    # dlopen is in -lc on QNX
 	    DL_LIBS=""
-	    CC_SEARCH_FLAGS=""
-	    LD_SEARCH_FLAGS=""
+	    LDFLAGS="$LDFLAGS -Wl,--export-dynamic"
+	    CC_SEARCH_FLAGS='-Wl,-rpath,${LIB_RUNTIME_DIR}'
+	    LD_SEARCH_FLAGS=${CC_SEARCH_FLAGS}
+	    SHARED_LIB_SUFFIX='${TCL_TRIM_DOTS}\$\{DBGX\}.so'
+	    UNSHARED_LIB_SUFFIX='${TCL_TRIM_DOTS}\$\{DBGX\}.a'
+	    TCL_LIB_VERSIONS_OK=nodots
 	    ;;
 	SCO_SV-3.2*)
 	    # Note, dlopen is available only on SCO 3.2.5 and greater. However,
