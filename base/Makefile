#===========================================================================#
#																			#
#	Base System Makefile													#
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
LIBRARY = libViper3D.a

# Source Files
SRCS =	VInput.cpp \
		VWindow.cpp \
		VNode.cpp \
		VMovable.cpp \
		VCamera.cpp \
		VProfiler.cpp \
		Viper3D.cpp

# Object Files
OBJS = $(SRCS:.cpp=.o)

# Main target
all : $(LIB)
.PHONY: all

# Library build
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
