#===========================================================================#
#																			#
#	Viper3D Game Engine Main Makefile										#
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

BUILD_LIBS = \
		base-lib \
		math-lib \
		util-lib \
		X-Input-lib \
		X-Window-lib

all : $(BUILD_LIBS)
	@echo -e "\n*==================================*"
	@echo -e "* All libraries built successfully *"
	@echo -e "*==================================*\n"

.PHONY: all
#############################
#		Build Targets		#
#############################
# Base system library
base-lib :
	@echo -e "\n================================*"
	@echo -e "* Creating Base Viper3D library *"
	@echo -e "*===============================*\n"
	@$(MAKE) -C base 

# Math library
math-lib :
	@echo -e "\n================================*"
	@echo -e "* Creating Viper3D Math library *"
	@echo -e "*===============================*\n"
	@$(MAKE) -C math

# Utility library
util-lib :
	@echo -e "\n================================*"
	@echo -e "* Creating Viper3d Utility lib  *"
	@echo -e "*===============================*\n"
	@$(MAKE) -C util

# X InputSystem shared library
X-Input-lib :
	@echo -e "\n================================*"
	@echo -e "*  Creating XInput System lib   *"
	@echo -e "*===============================*\n"
	@$(MAKE) -C InputSystems/X

# X WindowSystem shared library
X-Window-lib:
	@echo -e "\n================================*"
	@echo -e "*  Creating XWindow System lib  *"
	@echo -e "*===============================*\n"
	@$(MAKE) -C WindowSystems/X

# Doxygen documentation
docs:
	@doxygen .doxy-conf
	
clean: clean-base clean-math clean-util clean-X-Input clean-X-Window
clean-all: clean clean-libs clean-docs
#############################
#		Clean Targets		#
#############################
clean-base:
	$(MAKE) -C base clean
clean-math:
	$(MAKE) -C math clean
clean-util:
	$(MAKE) -C util clean
clean-X-Input:
	$(MAKE) -C InputSystems/X clean
clean-X-Window:
	$(MAKE) -C WindowSystems/X clean
clean-libs:
	@echo -e "\n * Cleaning libraries *\n"
	@$(RM) $(OUTPUT_DIR)/*.so $(OUTPUT_DIR)/*.a
clean-docs:
	@$(RM) -r docs

