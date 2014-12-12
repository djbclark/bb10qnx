$NetBSD$

--- Modules/signalmodule.c.orig	2013-05-15 16:32:59.000000000 +0000
+++ Modules/signalmodule.c
@@ -742,7 +742,11 @@ fill_siginfo(siginfo_t *si)
     PyStructSequence_SET_ITEM(result, 4, _PyLong_FromUid(si->si_uid));
     PyStructSequence_SET_ITEM(result, 5,
                                 PyLong_FromLong((long)(si->si_status)));
+#ifndef __QNXNTO__
     PyStructSequence_SET_ITEM(result, 6, PyLong_FromLong(si->si_band));
+#else
+    PyStructSequence_SET_ITEM(result, 6, PyLong_FromLong(-1L));
+#endif
     if (PyErr_Occurred()) {
         Py_DECREF(result);
         return NULL;
