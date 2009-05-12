CC			= g++
RM			= rm -f

LIBS		= -lViper3D -lVMath -lVUtil -ldl -lGL -lXxf86vm

VIPER_PATH	= ../

LIB_PATH	= -L$(VIPER_PATH)/libs -L/usr/X11R6/lib

INC_PATH	=	-I$(VIPER_PATH)base \
				-I$(VIPER_PATH)util \
				-I$(VIPER_PATH)math \
				-I$(VIPER_PATH)input \
				-I$(VIPER_PATH)window \
				-I$(VIPER_PATH)interfaces

CFLAGS		= -Wall -pedantic -ansi -O2 -DDEBUG

OBJS		=	engtest2.o \
				vectest.o \
				matrixtest.o

EXEC		= engtest2

all : $(EXEC)
.PHONY: all

$(EXEC) : $(OBJS)
	@echo -e "\n*=======================*"
	@echo -e "*  Creating Executable  *"
	@echo -e "*=======================*\n"
	$(CC) -o $(EXEC) $(OBJS) $(LIB_PATH) $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $(INC_PATH) -c -o $@ $<

clean:
	$(RM) *.o $(EXEC)
