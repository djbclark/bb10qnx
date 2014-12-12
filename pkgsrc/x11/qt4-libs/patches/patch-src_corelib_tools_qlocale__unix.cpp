$NetBSD$

--- src/corelib/tools/qlocale_unix.cpp.orig	2013-06-07 05:16:52.000000000 +0000
+++ src/corelib/tools/qlocale_unix.cpp
@@ -45,6 +45,9 @@
 #include "qdatetime.h"
 #include "qstringlist.h"
 #include "qvariant.h"
+#ifdef Q_OS_QNX
+#include <unistd.h>
+#endif
 
 QT_BEGIN_NAMESPACE
 
