# $NetBSD: Makefile,v 1.6 2012/10/29 05:06:09 asau Exp $
#

DISTNAME=		damageproto-1.2.1
CATEGORIES=		x11 devel
MASTER_SITES=		${MASTER_SITE_XORG:=proto/}
EXTRACT_SUFX=		.tar.bz2

MAINTAINER=		joerg@NetBSD.org
HOMEPAGE=		http://xorg.freedesktop.org/
COMMENT=		Damage extension headers from modular X.org

GNU_CONFIGURE=		yes
PKGCONFIG_OVERRIDE+=	damageproto.pc.in
# for configure
USE_LANGUAGES=		c

.include "../../x11/xproto/buildlink3.mk"
.include "../../x11/fixesproto/buildlink3.mk"

.include "../../mk/bsd.pkg.mk"
