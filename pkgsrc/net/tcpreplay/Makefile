# $NetBSD: Makefile,v 1.21 2013/02/06 19:31:01 jperkin Exp $

DISTNAME=	tcpreplay-3.4.1
PKGREVISION=	1
CATEGORIES=	net
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=tcpreplay/}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://tcpreplay.synfin.net/
COMMENT=	Replay saved tcpdump or snoop files

BUILDLINK_API_DEPENDS.libpcap+=	libpcap>=0.8.0

GNU_CONFIGURE=	yes
USE_LIBTOOL=	yes

CONFIGURE_ARGS+=	--enable-dynamic-link
CONFIGURE_ARGS+=	--with-libpcap=${BUILDLINK_PREFIX.libpcap}

LIBS.QNX+=	-lsocket
.include "../../mk/bsd.prefs.mk"
.if ${OPSYS} == "QNX"
# likes to free() buffer returned from pathfind and ours doesn't malloc.
CONFIGURE_ENV+=		ac_cv_lib_gen_pathfind=no
CONFIGURE_ENV+=		libopts_cv_run_pathfind=no
.endif

.include "../../net/libpcap/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
