$NetBSD$

--- lib/replace/replace.c.orig	2012-04-11 12:36:12.000000000 +0000
+++ lib/replace/replace.c
@@ -536,6 +536,24 @@ long long int rep_strtoll(const char *st
 	}
 	return nb;
 }
+#elif defined(__QNXNTO__)
+long long int rep_strtoll(const char *str, char **endptr, int base)
+{
+	long long int nb;
+	errno = EOK;
+	nb = strtoll(str, endptr, base);
+	/* In linux EINVAL is only returned if base is not ok */
+	if (errno == EINVAL) {
+		if (base == 0 || (base >1 && base <37)) {
+			/* Base was ok so it's because we were not
+			 * able to make the convertion.
+			 * Let's reset errno.
+			 */
+			errno = 0;
+		}
+	}
+	return nb;
+}
 #else
 #error "You need the strtoq function"
 #endif /* HAVE_STRTOQ */
@@ -574,6 +592,24 @@ unsigned long long int rep_strtoull(cons
 	}
 	return nb;
 }
+#elif defined(__QNXNTO__)
+unsigned long long int rep_strtoull(const char *str, char **endptr, int base)
+{
+	unsigned long long int nb;
+	errno = EOK;
+	nb = strtoull(str, endptr, base);
+	/* In linux EINVAL is only returned if base is not ok */
+	if (errno == EINVAL) {
+		if (base == 0 || (base >1 && base <37)) {
+			/* Base was ok so it's because we were not
+			 * able to make the convertion.
+			 * Let's reset errno.
+			 */
+			errno = 0;
+		}
+	}
+	return nb;
+}
 #else
 #error "You need the strtouq function"
 #endif /* HAVE_STRTOUQ */
