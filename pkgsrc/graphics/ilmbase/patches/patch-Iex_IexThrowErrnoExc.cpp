$NetBSD: patch-Iex_IexThrowErrnoExc.cpp,v 1.2 2013/05/08 17:48:33 adam Exp $

--- Iex/IexThrowErrnoExc.cpp.orig	2013-02-04 18:22:35.000000000 +0000
+++ Iex/IexThrowErrnoExc.cpp
@@ -419,7 +419,7 @@ void throwErrnoExc (const std::string &t
 	    throw EnametoolongExc (tmp);
       #endif
 
-      #if defined (EOVERFLOW)
+      #if defined (EOVERFLOW) && EOVERFLOW != ERANGE
 	  case EOVERFLOW:
 	    throw EoverflowExc (tmp);
       #endif
@@ -629,7 +629,7 @@ void throwErrnoExc (const std::string &t
 	    throw EhostunreachExc (tmp);
       #endif
 
-      #if defined (EALREADY)
+      #if defined (EALREADY) && ((EALREADY) != (EBUSY))
 	  case EALREADY:
 	    throw EalreadyExc (tmp);
       #endif
