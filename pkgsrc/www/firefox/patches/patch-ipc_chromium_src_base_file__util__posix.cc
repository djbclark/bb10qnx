$NetBSD: patch-ipc_chromium_src_base_file__util__posix.cc,v 1.1 2013/07/17 11:00:13 jperkin Exp $

--- ipc/chromium/src/base/file_util_posix.cc.orig	2013-06-18 11:01:23.000000000 +0000
+++ ipc/chromium/src/base/file_util_posix.cc
@@ -8,13 +8,15 @@
 #include <errno.h>
 #include <fcntl.h>
 #include <fnmatch.h>
-#ifndef ANDROID
+#if !defined(ANDROID) && !defined(OS_SOLARIS) && !defined(OS_QNX)
 #include <fts.h>
 #endif
 #include <libgen.h>
 #include <stdio.h>
 #include <string.h>
+#ifndef OS_QNX
 #include <sys/errno.h>
+#endif
 #include <sys/mman.h>
 #define _DARWIN_USE_64_BIT_INODE // Use 64-bit inode data structures
 #include <sys/stat.h>
@@ -121,7 +123,7 @@ bool Delete(const FilePath& path, bool r
   if (!recursive)
     return (rmdir(path_str) == 0);
 
-#ifdef ANDROID
+#if defined(ANDROID) || defined(OS_SOLARIS) || defined(OS_QNX)
   // XXX Need ftsless impl for bionic
   return false;
 #else
@@ -194,7 +196,7 @@ bool CopyDirectory(const FilePath& from_
     return false;
   }
 
-#ifdef ANDROID
+#if defined(ANDROID) || defined(OS_SOLARIS) || defined(OS_QNX)
   // XXX Need ftsless impl for bionic
   return false;
 #else
@@ -613,7 +615,7 @@ FileEnumerator::FileEnumerator(const Fil
 }
 
 FileEnumerator::~FileEnumerator() {
-#ifndef ANDROID
+#if !defined(ANDROID) && !defined(OS_SOLARIS) && !defined(OS_QNX)
   if (fts_)
     fts_close(fts_);
 #endif
@@ -625,7 +627,7 @@ void FileEnumerator::GetFindInfo(FindInf
   if (!is_in_find_op_)
     return;
 
-#ifndef ANDROID
+#if !defined(ANDROID) && !defined(OS_SOLARIS) && !defined(OS_QNX)
   memcpy(&(info->stat), fts_ent_->fts_statp, sizeof(info->stat));
   info->filename.assign(fts_ent_->fts_name);
 #endif
@@ -636,7 +638,7 @@ void FileEnumerator::GetFindInfo(FindInf
 // large directories with many files this can be quite deep.
 // TODO(erikkay) - get rid of this recursive pattern
 FilePath FileEnumerator::Next() {
-#ifdef ANDROID
+#if defined(ANDROID) || defined(OS_SOLARIS) || defined(OS_QNX)
   return FilePath();
 #else
   if (!is_in_find_op_) {
