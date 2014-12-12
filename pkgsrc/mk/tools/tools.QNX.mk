#
# System-supplied tools for the QNX operating system.

TOOLS_PLATFORM.[?=		[			# shell builtin
TOOLS_PLATFORM.awk?=		/bin/awk
TOOLS_PLATFORM.basename?=	/usr/bin/basename
#.if exists(${QNX_HOST}/usr/bin/bison)
TOOLS_PLATFORM.bison?=          ${QNX_HOST}/bin/bison
TOOLS_PLATFORM.bison-yacc?=     ${QNX_HOST}/bin/bison -y
#.endif
#.if exists(/usr/bin/bzcat)
TOOLS_PLATFORM.bzcat?=		${QNX_HOST}/bin/bzcat
#.endif
TOOLS_PLATFORM.bzip2?=		${QNX_HOST}/bin/bzip2
TOOLS_PLATFORM.cat?=		/bin/cat
TOOLS_PLATFORM.chgrp?=		/bin/chgrp
TOOLS_PLATFORM.chmod?=		/bin/chmod
TOOLS_PLATFORM.chown?=		/bin/chown
TOOLS_PLATFORM.cmp?=		${QNX_HOST}/bin/cmp
TOOLS_PLATFORM.cp?=		/bin/cp
TOOLS_PLATFORM.cut?=		/usr/bin/cut
TOOLS_PLATFORM.date?=		/usr/bin/date
TOOLS_PLATFORM.diff?=		${QNX_HOST}/bin/diff
TOOLS_PLATFORM.diff3?=		${QNX_HOST}/bin/diff3
TOOLS_PLATFORM.dirname?=	/usr/bin/dirname
TOOLS_PLATFORM.echo?=		echo			# shell builtin
TOOLS_PLATFORM.egrep?=		${QNX_HOST}/bin/egrep
TOOLS_PLATFORM.env?=		/usr/bin/env
TOOLS_PLATFORM.expr?=		/usr/bin/expr
TOOLS_PLATFORM.false?=		false			# shell builtin
TOOLS_PLATFORM.fgrep?=		${QNX_HOST}/bin/fgrep
TOOLS_PLATFORM.file?=		${QNX_HOST}/bin/file
TOOLS_PLATFORM.find?=		/usr/bin/find
.if exists(${QNX_HOST}/usr/bin/flex)
TOOLS_PLATFORM.flex?=		${QNX_HOST}/usr/bin/flex
.endif
#TOOLS_PLATFORM.ftp?=		/usr/bin/ftp

TOOLS_PLATFORM.gawk?=		/bin/gawk
TOOLS_PLATFORM.grep?=		/usr/bin/grep
#.if exists(${QNX_HOST}/usr/bin/groff)
TOOLS_PLATFORM.groff?=		${QNX_HOST}/bin/groff
#.endif
TOOLS_PLATFORM.gunzip?=		${QNX_HOST}/bin/gunzip -f
TOOLS_PLATFORM.gzcat?=		${QNX_HOST}/bin/gzip -dc
TOOLS_PLATFORM.gzip?=		${QNX_HOST}/bin/gzip -nf ${GZIP}
TOOLS_PLATFORM.head?=		${QNX_HOST}/bin/head
TOOLS_PLATFORM.hostname?=	/bin/hostname
TOOLS_PLATFORM.id?=		${QNX_HOST}/bin/id 2>/dev/null
.if exists(/sbin/ldconfig)
TOOLS_PLATFORM.ldconfig?=	/sbin/ldconfig
.endif
TOOLS_PLATFORM.ksh?=		/bin/ksh
.if exists(${QNX_HOST}/usr/bin/lex)
TOOLS_PLATFORM.lex?=		${QNX_HOST}/usr/bin/lex
.endif
TOOLS_PLATFORM.ln?=		/bin/ln
TOOLS_PLATFORM.ls?=		/bin/ls
.if exists(/usr/bin/m4)
TOOLS_PLATFORM.m4?=		/usr/bin/m4
.endif
.if exists(/usr/bin/mail)
TOOLS_PLATFORM.mail?=		/usr/bin/mail
.endif
#.if exists(${QNX_HOST}/usr/bin/make)
TOOLS_PLATFORM.gmake?=           ${QNX_HOST}/bin/make
#.endif
.if exists(/usr/bin/makeinfo)
TOOLS_PLATFORM.makeinfo?=	/usr/bin/makeinfo
.endif
TOOLS_PLATFORM.mkdir?=		${QNX_HOST}/bin/mkdir -p
#.if exists(/usr/bin/mktemp)
TOOLS_PLATFORM.mktemp?=		${QNX_HOST}/bin/mktemp
#.endif
#.if exists(/usr/bin/msgfmt)
TOOLS_PLATFORM.msgfmt?=		${QNX_HOST}/bin/msgfmt
#.endif
.if exists(/usr/sbin/mtree)
TOOLS_PLATFORM.mtree?=		/usr/sbin/mtree
.endif
TOOLS_PLATFORM.mv?=		/bin/mv
TOOLS_PLATFORM.nice?=		${QNX_HOST}/bin/nice
#.if exists(${QNX_HOST}/usr/bin/nroff)
TOOLS_PLATFORM.nroff?=		${QNX_HOST}/bin/nroff
#.endif
.if exists(/usr/bin/openssl)
TOOLS_PLATFORM.openssl?=	/usr/bin/openssl
.endif
#.if exists(/usr/bin/patch)
TOOLS_PLATFORM.patch?=		${QNX_HOST}/bin/patch
#.endif
TOOLS_PLATFORM.printf?=		${QNX_HOST}/bin/printf
TOOLS_PLATFORM.pwd?=		pwd
.if empty(USE_CROSS_COMPILE:M[yY][eE][sS])
TOOLS_PLATFORM.readelf?=	${QNX_HOST}/bin/readelf
.else
TOOLS_PLATFORM.readelf?=	${QNX_HOST}/usr/bin/nto${MACHINE_GNU_PLATFORM}-readelf
.endif
TOOLS_PLATFORM.rm?=		${QNX_HOST}/bin/rm
TOOLS_PLATFORM.rmdir?=		${QNX_HOST}/bin/rmdir
#.if exists(/usr/bin/sdiff)
TOOLS_PLATFORM.sdiff?=		${QNX_HOST}/bin/sdiff
#.endif
TOOLS_PLATFORM.sed?=		/bin/sed
TOOLS_PLATFORM.sh?=		/bin/sh
.if exists(/usr/bin/shlock)
TOOLS_PLATFORM.shlock?=		/usr/bin/shlock
.endif
TOOLS_PLATFORM.sleep?=		/usr/bin/sleep
#.if exists(${QNX_HOST}/usr/bin/soelim)
TOOLS_PLATFORM.soelim?=		${QNX_HOST}/bin/soelim
#.endif
TOOLS_PLATFORM.sort?=		/usr/bin/sort
.if empty(USE_CROSS_COMPILE:M[yY][eE][sS])
TOOLS_PLATFORM.strip?=		${QNX_HOST}/bin/strip
.else
TOOLS_PLATFORM.strip?=		${QNX_HOST}/usr/bin/nto${MACHINE_GNU_PLATFORM}-strip
.endif

TOOLS_PLATFORM.tail?=		/usr/bin/tail
.if exists(/usr/bin/tar)
TOOLS_PLATFORM.tar?=		/usr/bin/tar
.elif exists(/bin/tar)
TOOLS_PLATFORM.tar?=		/bin/tar
.endif
#.if exists(${QNX_HOST}/usr/bin/tbl)
TOOLS_PLATFORM.tbl?=		${QNX_HOST}/bin/tbl
#.endif
TOOLS_PLATFORM.tee?=		${QNX_HOST}/bin/tee
TOOLS_PLATFORM.test?=		test			# shell builtin
TOOLS_PLATFORM.touch?=		/usr/bin/touch
TOOLS_PLATFORM.tr?=		${QNX_HOST}/bin/tr
TOOLS_PLATFORM.true?=		true			# shell builtin
#.if exists(/usr/bin/tsort)
TOOLS_PLATFORM.tsort?=		${QNX_HOST}/bin/tsort
#.endif
TOOLS_PLATFORM.wc?=		/usr/bin/wc
TOOLS_PLATFORM.xargs?=		${QNX_HOST}/bin/xargs -r
TOOLS_PLATFORM.unzip?=		/usr/bin/unzip
#TOOLS_PLATFORM.xargs?=		/usr/bin/xargs
#.if exists(/usr/bin/xgettext)
TOOLS_PLATFORM.xgettext?=	${QNX_HOST}/bin/xgettext
#.endif
TOOLS_PLATFORM.yacc?=		${QNX_HOST}/bin/bison -y
