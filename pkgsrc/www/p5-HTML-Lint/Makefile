# $NetBSD: Makefile,v 1.9 2013/05/31 12:42:41 wiz Exp $

DISTNAME=	HTML-Lint-2.10
PKGNAME=	p5-${DISTNAME}
PKGREVISION=	2
CATEGORIES=	www perl5
MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=HTML/}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://search.cpan.org/dist/HTML-Lint/
COMMENT=	Perl 5 module to check for HTML errors in a string or file

USE_LANGUAGES=	# empty
PERL5_PACKLIST= auto/HTML/Lint/.packlist

DEPENDS+=	p5-HTML-Parser>=3.20:../../www/p5-HTML-Parser
DEPENDS+=	p5-HTML-Tagset>=3.03:../../www/p5-HTML-Tagset
DEPENDS+=	p5-libwww-[0-9]*:../../www/p5-libwww

.include "../../lang/perl5/module.mk"
.include "../../mk/bsd.pkg.mk"
