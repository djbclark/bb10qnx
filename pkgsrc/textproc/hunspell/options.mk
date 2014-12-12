# $NetBSD: options.mk,v 1.4 2012/02/13 14:42:59 wiz Exp $

PKG_OPTIONS_VAR=		PKG_OPTIONS.hunspell
PKG_SUPPORTED_OPTIONS=		wide-curses langinfo
PKG_SUGGESTED_OPTIONS=		# empty

PLIST_VARS+=	langinfo

.include "../../mk/bsd.options.mk"

USE_NCURSES=	yes

.if ${OPSYS} != "QNX"
PKG_SUGGESTED_OPTIONS+=		langinfo
PLIST.langinfo=			yes
.else
CONFIGURE_ARGS+=	--disable-nls
LIBS+=			-liconv
.endif

###
### Wide curses support; otherwise, default to using narrow curses.
###
.if !empty(MACHINE_PLATFORM:MNetBSD-[5-9].*-*)
   CONFIGURE_ENV+=	ac_cv_lib_curses_tparm=yes
.  include "../../mk/curses.buildlink3.mk"
.else
.  if !empty(PKG_OPTIONS:Mwide-curses)
.    include "../../devel/ncursesw/buildlink3.mk"
.  else
.    include "../../devel/ncurses/buildlink3.mk"
.  endif
.endif
