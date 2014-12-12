$NetBSD: patch-cxx_cursesf.h,v 1.1 2011/02/28 11:02:46 adam Exp $

--- c++/cursesf.h.orig	2005-08-13 18:08:24.000000000 +0000
+++ c++/cursesf.h
@@ -38,9 +38,7 @@
 
 #include <cursesp.h>
 
-#ifndef __EXT_QNX
 #include <string.h>
-#endif
 
 extern "C" {
 #  include <form.h>
@@ -677,7 +675,7 @@ protected:
   }
 
 public:
-  NCursesUserForm (NCursesFormField Fields[],
+  NCursesUserForm (NCursesFormField *Fields[],
 		   const T* p_UserData = STATIC_CAST(T*)(0),
 		   bool with_frame=FALSE,
 		   bool autoDelete_Fields=FALSE)
@@ -686,7 +684,7 @@ public:
 	set_user (const_cast<void *>(p_UserData));
   };
 
-  NCursesUserForm (NCursesFormField Fields[],
+  NCursesUserForm (NCursesFormField *Fields[],
 		   int nlines,
 		   int ncols,
 		   int begin_y = 0,
