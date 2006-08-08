#===========================================================================#
#																			#
#	Viper3D Utility Library Makefile										#
#																			#
#	Author:	Josh Williams													#
#																			#
#	Date:	06-Sep-2004														#
#																			#
#===========================================================================#
#																			#
# 	This file is part of the Viper3D Game Engine.							#
#																			#
#	Copyright (C) 2004 UDP Games   All Rights Reserved.						#
#																			#
#===========================================================================#
BASE_DIR = $(shell pwd | sed 's/viper3d.*/viper3d/')
include $(BASE_DIR)/Make.defs

# Library Name
LIBRARY = libVUtil.a

# Source Files
SRCS =	VDynamicLib.cpp \
		VString.cpp \
		VCPU.cpp \
		VLog.cpp

OBJS = $(SRCS:.cpp=.o)

all : $(LIB)
.PHONY: all

$(LIB) : $(OBJS)
	$(LD) $(LIB) $(OBJS)
	$(RANLIB) $(LIB)
	@echo -e "\n * Library created successfully *\n"

%.o: %.cpp
	$(COMPILE_CPP) $@ $<
	@$(MAKEDEPEND)

-include $(SRCS:%.cpp=$(DEPDIR)/%.P)

clean:
	$(RM) $(OBJS)

clean-lib:
	$(RM) $(LIB)

clean-all: clean clean-lib
