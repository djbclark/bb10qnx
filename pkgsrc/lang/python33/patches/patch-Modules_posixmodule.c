$NetBSD$

--- Modules/posixmodule.c.orig	2012-09-29 08:00:45.000000000 +0000
+++ Modules/posixmodule.c
@@ -11570,7 +11570,7 @@ all_ins(PyObject *d)
     if (ins(d, "SCHED_FIFO", (long)SCHED_FIFO)) return -1;
     if (ins(d, "SCHED_RR", (long)SCHED_RR)) return -1;
 #ifdef SCHED_SPORADIC
-    if (ins(d, "SCHED_SPORADIC", (long)SCHED_SPORADIC) return -1;
+    if (ins(d, "SCHED_SPORADIC", (long)SCHED_SPORADIC)) return -1;
 #endif
 #ifdef SCHED_BATCH
     if (ins(d, "SCHED_BATCH", (long)SCHED_BATCH)) return -1;
