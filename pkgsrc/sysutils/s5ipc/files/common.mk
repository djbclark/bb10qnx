# This is an automatically generated record.
# The area between QNX Internal Start and QNX Internal End is controlled by
# the QNX IDE properties.


ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

NAME=s5ipc

EXTRA_INCVPATH+=	$(PROJECT_ROOT)/manager/inc

EXTRA_SILENT_VARIANTS=	$(SECTION)

include $(MKFILES_ROOT)/qmacros.mk

include $(SECTION_ROOT)/$(SECTION).mk

include $(MKFILES_ROOT)/qtargets.mk
