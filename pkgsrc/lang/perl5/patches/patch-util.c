$NetBSD$

--- util.c.orig	2013-05-09 13:47:39.000000000 +0000
+++ util.c
@@ -2825,12 +2825,30 @@ Perl_atfork_unlock(void)
 #if defined(USE_ITHREADS)
     /* locks must be released in same order as in atfork_lock() */
 #  ifdef USE_PERLIO
+#    ifndef __QNXNTO__
     MUTEX_UNLOCK(&PL_perlio_mutex);
+#    else
+    if (pthread_mutex_init(&PL_perlio_mutex, NULL) != EOK) {
+	    MUTEX_UNLOCK(&PL_perlio_mutex);
+    }
+#    endif
 #  endif
 #  ifdef MYMALLOC
+#    ifndef __QNXNTO__
     MUTEX_UNLOCK(&PL_malloc_mutex);
+#    else
+    if (pthread_mutex_init(&PL_malloc_mutex, NULL) != EOK) {
+	    MUTEX_UNLOCK(&PL_malloc_mutex);
+    }
+#    endif
 #  endif
+#    ifndef __QNXNTO__
     OP_REFCNT_UNLOCK;
+#    else
+    if (pthread_mutex_init(&PL_op_mutex, NULL) != EOK) {
+	    OP_REFCNT_UNLOCK;
+    }
+#    endif
 #endif
 }
 
