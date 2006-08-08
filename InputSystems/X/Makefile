#===========================================================================#
#																			#
#	XInputSystem Makefile													#
#																			#
#	Author:	Josh Williams													#
#																			#
#	Date:	01-Sep-2004														#
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
LIBRARY = libVXInput.so

# Source Files
SRCS =	VXInputSystem.cpp

# Object Files
OBJS = $(SRCS:.cpp=.o)

all : $(LIB)
.PHONY: all

$(LIB) : $(OBJS)
	$(CXX) -shared $(OBJS) -o $(LIB)
	@echo -e "\n * Library created successfully *\n"

%.o: %.cpp
	$(COMPILE_CPP_SO) $@ $<
	@$(MAKEDEPEND)

-include $(SRCS:%.cpp=$(DEPDIR)/%.P)

clean:
	$(RM) $(OBJS)

clean-lib:
	$(RM) $(LIB)

clean-all: clean clean-lib
