# $NetBSD: Makefile,v 1.3 2013/06/14 14:46:12 tsutsui Exp $

DISTNAME=	tw-0.4.2
CATEGORIES=	net

MAINTAINER=	tsutsui@NetBSD.org
HOMEPAGE=	http://shokai.github.io/tw/
COMMENT=	CUI Twitter Client
LICENSE=	mit

DEPENDS+=	${RUBY_PKGPREFIX}-args_parser>=0.1.4:../../misc/ruby-args_parser
DEPENDS+=	${RUBY_PKGPREFIX}-parallel>=0.6.0:../../misc/ruby-parallel
DEPENDS+=	${RUBY_PKGPREFIX}-rainbow>=1.1.4:../../misc/ruby-rainbow
DEPENDS+=	${RUBY_PKGPREFIX}-twitter>=4.4.0:../../net/ruby-twitter
DEPENDS+=	${RUBY_PKGPREFIX}-userstream>=1.2.0:../../net/ruby-userstream

RUBY_JSON_REQD=	1.7.0

.include "../../lang/ruby/gem.mk"
.include "../../lang/ruby/json.mk"
.include "../../mk/bsd.pkg.mk"
