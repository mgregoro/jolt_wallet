#
# Component Makefile
#

COMPONENT_SRCDIRS := . \
	nanopb/
    
COMPONENT_ADD_INCLUDEDIRS := $(COMPONENT_SRCDIRS)

CFLAGS += \
		  -DPB_ENABLE_MALLOC
