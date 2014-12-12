if [ "x" = "x$QNX_ROOT" ] ; then
	QNX_ROOT=/usr/qnx650
fi

if [ "x" = "x$QNX_CONFIGURATION" ] ; then
	QNX_CONFIGURATION=/etc/qnx
	export QNX_CONFIGURATION
fi

QNX_HOST=$QNX_ROOT/host/qnx6/x86
QNX_TARGET=$QNX_ROOT/target/qnx6
MAKEFLAGS=-I$QNX_TARGET/usr/include
PATH=$PATH:$QNX_HOST/usr/bin:$QNX_HOST/usr/sbin:$QNX_HOST/sbin:$QNX_HOST/bin:$QNX_HOST/usr/photon/appbuilder
QNX_HELP_PATH=$QNX_TARGET/usr/help/product
QNX_HELP_HOME_PAGE=$QNX_TARGET/usr/help/product/momentics/bookset.html

export QNX_HOST QNX_TARGET MAKEFLAGS PATH QNX_HELP_PATH QNX_HELP_HOME_PAGE
