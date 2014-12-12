$NetBSD: patch-lib_rdoc_ri_driver.rb,v 1.1 2013/07/21 02:32:58 taca Exp $

* Defer loading readline, when it is really needed.
  Some unknown reason:

1. build devel/ruby-readline with editline(3).
2. Execute a ruby script loading readline in background from shell.
3. When the script output something to stdout, it got SIGTSTP and suspends.

There is no such problem when build devel/ruby-readline with GNU's readline.

--- lib/rdoc/ri/driver.rb.orig	2012-12-03 23:32:39.000000000 +0000
+++ lib/rdoc/ri/driver.rb
@@ -2,11 +2,6 @@ require 'abbrev'
 require 'optparse'
 
 begin
-  require 'readline'
-rescue LoadError
-end
-
-begin
   require 'win32console'
 rescue LoadError
 end
@@ -1053,6 +1048,11 @@ The ri pager can be set with the 'RI_PAG
   # Runs ri interactively using Readline if it is available.
 
   def interactive
+    begin
+      require 'readline'
+    rescue LoadError
+    end
+
     puts "\nEnter the method name you want to look up."
 
     if defined? Readline then
