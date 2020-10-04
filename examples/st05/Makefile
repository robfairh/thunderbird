###############################################################################
################### MOOSE Application Standard Makefile #######################
###############################################################################
#
# Optional Environment variables
# MOOSE_DIR     - Root directory of the MOOSE project
#
###############################################################################
# Use the MOOSE submodule if it exists and MOOSE_DIR is not set
MOOSE_SUBMODULE    := $(CURDIR)/../../../moose
ifneq ($(wildcard $(MOOSE_SUBMODULE)/framework/Makefile),)
  MOOSE_DIR        ?= $(MOOSE_SUBMODULE)
else
  MOOSE_DIR        ?= $(shell dirname `pwd`)/../../../moose
endif

# framework
EXAMPLE_DIR        ?= $(shell dirname `pwd`)
FRAMEWORK_DIR      := $(MOOSE_DIR)/framework
ADDITIONAL_CPPFLAGS += -Wall -Wextra
###############################################################################

 TEST := test_ignore

# framework
include $(FRAMEWORK_DIR)/build.mk
include $(FRAMEWORK_DIR)/moose.mk

APPLICATION_NAME := st05

# dep apps
APPLICATION_DIR    := $(shell pwd)
APPLICATION_NAME   := st05
BUILD_EXEC         := yes
include            $(FRAMEWORK_DIR)/app.mk

# Include dependency files for this example
ex_srcfiles := $(shell find $(APPLICATION_DIR) -name "*.C")
ex_deps     := $(patsubst %.C, %.$(obj-suffix).d, $(ex_srcfiles))
-include $(ex_deps)

###############################################################################
# Additional special case targets should be added here

test: all
	$(call TEST_exodiff,st05.i,st05_out.e)
