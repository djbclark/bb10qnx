# $NetBSD: Makefile,v 1.8 2012/10/23 19:51:00 asau Exp $

DISTNAME=	eggdbus-0.6
PKGREVISION=	4
CATEGORIES=	sysutils
MASTER_SITES=	http://cgit.freedesktop.org/~david/eggdbus/snapshot/
EXTRACT_SUFX=	.tar.bz2

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://cgit.freedesktop.org/~david/eggdbus
COMMENT=	GObject bindings for DBus
LICENSE=	gnu-gpl-v2

MAKE_JOBS_SAFE=		no

USE_LIBTOOL=		yes
USE_TOOLS+=		aclocal autoconf autoheader automake gmake pkg-config
GNU_CONFIGURE=		yes
TEST_TARGET=		check
PKGCONFIG_OVERRIDE+=	eggdbus-1.pc.in

pre-configure:
	set -e; cd ${WRKSRC}; gtkdocize --flavour no-tmpl; \
	libtoolize -c -f; \
	aclocal; autoheader; automake -a --foreign -i; autoconf

.include "../../mk/bsd.prefs.mk"

.if ${OPSYS} == "QNX"
# At some point in the build an executable that links against
# glib2 is run. When HAVE_LANGINFO_CODESET isn't set
# _g_locale_charset_raw() goes to getenv() and pulls out
# 'LC_ALL', 'LC_CTYPE' and then 'LANG' in that order.  If
# any are set to 'C' later libiconv_open ("UTF-8", "C")
# fails as "C" isn't supported therein.  The latter two are
# set to "C" by bsd.pkg.mk.
MAKE_ENV=	LC_ALL=ASCII
.endif

.include "../../textproc/gtk-doc/buildlink3.mk"
.include "../../devel/glib2/buildlink3.mk"
.include "../../sysutils/dbus/buildlink3.mk"
.include "../../sysutils/dbus-glib/buildlink3.mk"
.include "../../textproc/gtk-doc/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
