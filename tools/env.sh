export NATIVE_TOOLS=/accounts/devuser/tools
pkgsrc=/accounts/devuser/pkg
QNX_TARGET=$NATIVE_TOOLS/target_10_2_0_1155/qnx6

PATH="$NATIVE_TOOLS/bin:$NATIVE_TOOLS/sbin:$pkgsrc/bin:$pkgsrc/sbin:$PATH"
LD_LIBRARY_PATH="$NATIVE_TOOLS/lib:$LD_LIBRARY_PATH"
#MAKEFLAGS="-I$NATIVE_TOOLS/include"
CS_LIBPATH="$pkgsrc/lib:$CS_LIBPATH"
MANPATH="$NATIVE_TOOLS/man:$NATIVE_TOOLS/share/man:$pkgsrc/share/man:$MANPATH"

export PATH LD_LIBRARY_PATH MAKEFLAGS CS_LIBPATH MANPATH

QNX_HOST="$NATIVE_TOOLS"
#QNX_CONFIGURATION="$NATIVE_TOOLS/etc/qnxconf"
QCONF_OVERRIDE=$NATIVE_TOOLS/qconf-override.mk
MAKEFLAGS="-I$QNX_TARGET/usr/include"
LD_LIBRARY_PATH="$QNX_TARGET/armle-v7/usr/lib:$LD_LIBRARY_PATH"
#PATH="$NATIVE_TOOLS/usr/bin:$PATH"

export QNX_TARGET QNX_HOST QCONF_OVERRIDE MAKEFLAGS LD_LIBRARY_PATH PATH

GROFF_FONT_PATH="$NATIVE_TOOLS/share/groff/1.19.2/font:$NATIVE_TOOLS/share/groff/site-font"
GROFF_TMAC_PATH="$NATIVE_TOOLS/share/groff/1.19.2/tmac:$NATIVE_TOOLS/share/groff/site-tmac"
export GROFF_FONT_PATH GROFF_TMAC_PATH

MAGIC="$NATIVE_TOOLS/share/misc/magic.mgc"
export MAGIC

alias man='man -C "$NATIVE_TOOLS/lib/man.conf"'
alias ls='ls --color=auto'
