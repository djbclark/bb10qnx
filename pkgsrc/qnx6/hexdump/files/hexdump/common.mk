# This is an automatically generated record.
# The area between QNX Internal Start and QNX Internal End is controlled by
# the QNX IDE properties.


ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

NAME=			hexdump
LINKS=			od
FLAGS+=			-Du_int=uint32_t -Du_char=uint8_t -Du_int16_t=uint16_t
FLAGS+=			-Du_int32_t=uint32_t -Du_int64_t=uint64_t
FLAGS+=			-Decalloc=calloc -Demalloc=malloc

include $(MKFILES_ROOT)/qtargets.mk

INSTALL_DIRECTORY=	$(LOCALBASE)/bin
