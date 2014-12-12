# 
#

DISTNAME=	s5ipc
PKGNAME=	s5ipc-0.1
CATEGORIES=	sysutils
MASTER_SITES=	# none
DISTFILES=	# none

MAINTAINER=	seanb@qnx.com
HOMEPAGE=	# none
COMMENT=	Library and QNX Resource Manager to support SysV ipc

ONLY_FOR_PLATFORM=	QNX-*-*


NO_CHECKSUM=	yes
USE_LANGUAGES=	# none
#AUTO_MKDIRS=	yes
USE_TOOLS+=	gmake

do-extract:
	${CP} -R ${FILESDIR} ${WRKSRC}

do-install:
	${INSTALL} -m 755 -d ${DESTDIR}${PREFIX}/include
	${INSTALL} -m 755 -d ${DESTDIR}${PREFIX}/include/sys
	${INSTALL} -m 755 -d ${DESTDIR}${PREFIX}/lib
	${INSTALL} -m 444 ${WRKDIR}/s5ipc/lib/public/sys/shm.h ${DESTDIR}${PREFIX}/include/sys/shm.h
	${INSTALL} -m 444 ${WRKDIR}/s5ipc/lib/public/sys/ipc.h ${DESTDIR}${PREFIX}/include/sys/ipc.h
	${INSTALL} -m 444 ${WRKDIR}/s5ipc/lib/x86/a/libs5ipc.a ${DESTDIR}${PREFIX}/lib/libs5ipc.a
	${INSTALL} -m 444 ${WRKDIR}/s5ipc/lib/x86/so/libs5ipcS.a ${DESTDIR}${PREFIX}/lib/libs5ipcS.a
	${INSTALL} -m 444 ${WRKDIR}/s5ipc/lib/x86/so/libs5ipc.so ${DESTDIR}${PREFIX}/lib/libs5ipc.so.1
	${LN} -s libs5ipc.so.1 ${DESTDIR}${PREFIX}/lib/libs5ipc.so
	${INSTALL} -m 444 ${WRKDIR}/s5ipc/manager/x86/o/s5ipc ${DESTDIR}${PREFIX}/sbin/s5ipc

.include "../../mk/bsd.pkg.mk"
