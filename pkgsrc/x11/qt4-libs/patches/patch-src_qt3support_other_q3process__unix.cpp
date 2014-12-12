$NetBSD$

--- src/qt3support/other/q3process_unix.cpp.orig	2013-06-07 05:16:58.000000000 +0000
+++ src/qt3support/other/q3process_unix.cpp
@@ -39,6 +39,9 @@
 **
 ****************************************************************************/
 
+#ifdef __QNXNTO__
+#include <sys/part.h>
+#endif
 #include "qplatformdefs.h"
 
 // Solaris redefines connect -> __xnet_connect with _XOPEN_SOURCE_EXTENDED.
@@ -65,6 +68,12 @@
 #include <stdlib.h>
 #include <errno.h>
 #include <sys/types.h>
+#ifdef Q_OS_QNX
+#include <sys/procmsg.h>
+__BEGIN_DECLS
+extern pid_t _fork(const unsigned int, const uintptr_t);
+__END_DECLS
+#endif
 
 QT_BEGIN_NAMESPACE
 
@@ -213,55 +222,6 @@ static void q3process_cleanup()
     Q3ProcessPrivate::procManager = 0;
 }
 
-#ifdef Q_OS_QNX
-#define BAILOUT qt_safe_close(tmpSocket);qt_safe_close(socketFD[1]);return -1;
-int qnx6SocketPairReplacement (int socketFD[2]) {
-    int tmpSocket;
-    tmpSocket = socket (AF_INET, SOCK_STREAM, 0);
-    if (tmpSocket == -1)
-	return -1;
-    socketFD[1] = socket(AF_INET, SOCK_STREAM, 0);
-    if (socketFD[1] == -1) { BAILOUT };
-
-    sockaddr_in ipAddr;
-    memset(&ipAddr, 0, sizeof(ipAddr));
-    ipAddr.sin_family = AF_INET;
-    ipAddr.sin_addr.s_addr = INADDR_ANY;
-
-    int socketOptions = 1;
-    setsockopt(tmpSocket, SOL_SOCKET, SO_REUSEADDR, &socketOptions, sizeof(int));
-
-    bool found = false;
-    for (int socketIP = 2000; (socketIP < 2500) && !(found); socketIP++) {
-	ipAddr.sin_port = htons(socketIP);
-	if (bind(tmpSocket, (struct sockaddr *)&ipAddr, sizeof(ipAddr)))
-	    found = true;
-    }
-
-    if (listen(tmpSocket, 5)) { BAILOUT };
-
-    // Select non-blocking mode
-    int originalFlags = fcntl(socketFD[1], F_GETFL, 0);
-    fcntl(socketFD[1], F_SETFL, originalFlags | O_NONBLOCK);
-
-    // Request connection
-    if (connect(socketFD[1], (struct sockaddr*)&ipAddr, sizeof(ipAddr)))
-	if (errno != EINPROGRESS) { BAILOUT };
-
-    // Accept connection
-    socketFD[0] = accept(tmpSocket, (struct sockaddr *)NULL, (QT_SOCKLEN_T *)NULL);
-    if(socketFD[0] == -1) { BAILOUT };
-
-    // We're done
-    qt_safe_close(tmpSocket);
-
-    // Restore original flags , ie return to blocking
-    fcntl(socketFD[1], F_SETFL, originalFlags);
-    return 0;
-}
-#undef BAILOUT
-#endif
-
 Q3ProcessManager::Q3ProcessManager() : sn(0)
 {
     procList = new Q3PtrList<QProc>;
@@ -270,11 +230,7 @@ Q3ProcessManager::Q3ProcessManager() : s
     // The SIGCHLD handler writes to a socket to tell the manager that
     // something happened. This is done to get the processing in sync with the
     // event reporting.
-#ifndef Q_OS_QNX
     if ( ::socketpair( AF_UNIX, SOCK_STREAM, 0, sigchldFd ) ) {
-#else
-    if ( qnx6SocketPairReplacement (sigchldFd) ) {
-#endif
 	sigchldFd[0] = 0;
 	sigchldFd[1] = 0;
     } else {
@@ -670,29 +626,17 @@ bool Q3Process::start( QStringList *env 
     int sStderr[2];
 
     // open sockets for piping
-#ifndef Q_OS_QNX
     if ( (comms & Stdin) && ::socketpair( AF_UNIX, SOCK_STREAM, 0, sStdin ) == -1 ) {
-#else
-    if ( (comms & Stdin) && qnx6SocketPairReplacement(sStdin) == -1 ) {
-#endif
 	return false;
     }
-#ifndef Q_OS_QNX
     if ( (comms & Stderr) && ::socketpair( AF_UNIX, SOCK_STREAM, 0, sStderr ) == -1 ) {
-#else
-    if ( (comms & Stderr) && qnx6SocketPairReplacement(sStderr) == -1 ) {
-#endif
 	if ( comms & Stdin ) {
 	    qt_safe_close( sStdin[0] );
 	    qt_safe_close( sStdin[1] );
 	}
 	return false;
     }
-#ifndef Q_OS_QNX
     if ( (comms & Stdout) && ::socketpair( AF_UNIX, SOCK_STREAM, 0, sStdout ) == -1 ) {
-#else
-    if ( (comms & Stdout) && qnx6SocketPairReplacement(sStdout) == -1 ) {
-#endif
 	if ( comms & Stdin ) {
 	    qt_safe_close( sStdin[0] );
 	    qt_safe_close( sStdin[1] );
@@ -754,7 +698,11 @@ bool Q3Process::start( QStringList *env 
 
     // fork and exec
     QApplication::flushX();
+#ifndef Q_OS_QNX
     pid_t pid = fork();
+#else
+    pid_t pid = _fork(_FORK_ASPACE, 0);
+#endif
     if ( pid == 0 ) {
 	// child
 	d->closeOpenSocketsForChild();
