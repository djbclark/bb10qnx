# $NetBSD: Makefile,v 1.93 2013/06/13 14:16:21 wiz Exp $

PKGNAME=	MesaLib-${MESA_PKGVERSION}
PKGREVISION=	2
COMMENT=	Graphics library similar to SGI's OpenGL

CONFLICTS+=	xf86driproto<2.0.4

PLIST_VARS=		dri nodri

PKGCONFIG_OVERRIDE+=	src/mesa/drivers/dri/dri.pc.in
PKGCONFIG_OVERRIDE+=	src/mesa/gl.pc.in
PKGCONFIG_OVERRIDE+=	src/mesa/osmesa.pc.in
PKGCONFIG_OVERRIDE+=	src/glw/glw.pc.in

CONFIGURE_ARGS+=        --disable-glu
CONFIGURE_ARGS+=        --disable-glut
CONFIGURE_ARGS+=        --disable-motif

.include "glx-config.mk"
.include "../../graphics/Mesa/Makefile.lib"
.include "options.mk"

.if !empty(MACHINE_PLATFORM:MNetBSD-[12].*)
##
## NetBSD 2.x and earlier require pthread stubs
##
.  include "../../devel/pthread-stublib/buildlink3.mk"
PTHREAD_STUBLIB= -L${PREFIX}/lib -Wl,-R${PREFIX}/lib -lpthstub
.elif !empty(MACHINE_PLATFORM:MNetBSD-*)
##
## NetBSD 3.x and later have pthread stubs in libc
##
PTHREAD_STUBLIB=
.else
##
## Other platforms may or may not have stubs provided by libc, but pulling in
## threading support via the pthread.buildlink3.mk definitions will provide
## all the necessary interfaces.  This matches the standard configuration for
## most platforms as they appear in "${WRKSRC}/configs", and is necessary
## for successful linking with libGL under many platforms.
##
.include "../../mk/pthread.buildlink3.mk"
PTHREAD_STUBLIB= ${PTHREAD_LDFLAGS} ${PTHREAD_LIBS}
.endif
PKGSRC_MAKE_ENV+=	PTHREAD_STUBLIB=${PTHREAD_STUBLIB:Q}
MAKE_ENV+=		PTHREAD_STUBLIB=${PTHREAD_STUBLIB:Q}

PTHREAD_LINKFLAGS=	${PTHREAD_LDFLAGS} ${PTHREAD_LIBS}
SUBST_CLASSES+=		pthread
SUBST_STAGE.pthread=	pre-configure
SUBST_MESSAGE.pthread=	Fixing config scripts.
SUBST_FILES.pthread=	configure.ac
SUBST_SED.pthread=	-e 's/-lpthread/${PTHREAD_LINKFLAGS:Q}/'

.if !empty(USE_CROSS_COMPILE:M[yY][eE][sS])
MAKE_ENV+=	CROSS_COMPILING=yes
.endif

post-extract:
.if !empty(PKG_OPTIONS:Mdri) && (${OPSYS} == "SunOS")
	${CP} ${FILESDIR}/mapfile.externs ${WRKSRC}/src/mesa/drivers/dri/
.endif
	${CP} ${FILESDIR}/gen_matypes.awk ${WRKSRC}/src/mesa/x86
	${CP} ${FILESDIR}/gen_matypes.sh ${WRKSRC}/src/mesa/x86
	${CHMOD} a+x ${WRKSRC}/src/mesa/x86/gen_matypes.sh

#
# remove include files installed respectively by ../glu and ../glut
#
pre-install:
	${RM} -f ${WRKSRC}/include/GL/glu*.h

.include "../../mk/compiler.mk"

.if !empty(PKGSRC_COMPILER:Mclang)
CFLAGS+=	-no-integrated-as -fvisibility=hidden
.endif

LDFLAGS.QNX+=	-Wl,-znotext	#PR 285396

.include "../../mk/bsd.pkg.mk"
.include "../../mk/pthread.buildlink3.mk"
.if ${OPSYS} == "QNX" && !empty(OS_VERSION:M[0-6].*)
LIBS+= -lgetopt
.include "../../devel/libgetopt/buildlink3.mk"
.endif
