CPP = g++

DEFS =
DIR_SUPPORT = support
DIR_CPU = cpu
DIR_PERIPHERAL = peripheral
INCDIR = -I. -I$(DIR_SUPPORT) -T$(DIR_CPU) -I$(DIR_PERIPHERAL)

CPPFLAGS = $(DEFS) $(INCDIR) -g -Wall -std=c++0x
LDFLAGS =

PROG = test

OBJS = main.o \
	support/schedule.o \
	cpu/cpu.o \
	cpu/bus_interface.o \
	peripheral/peripheral.o \
	peripheral/memory.o

SRCS = $(OBJS:.o=.cpp)

.cpp.o :
	@echo CPP $<
	@$(CPP) $(CPPFLAGS) -c $< -o $@

all : dep $(OBJS) tag
	@echo LINK $(PROG)
	@$(CPP) -o $(PROG).exe $(OBJS) $(LDFLAGS)

clean :
	@rm -f $(PROG).exe $(OBJS) .depend tags

tag :
	@ctags *.cpp *.h \
	$(DIR_SUPPORT)/*.cpp $(DIR_SUPPORT)/*.h \
	$(DIR_CPU)/*.cpp $(DIR_CPU)/*.h \
	$(DIR_PERIPHERAL)/*.cpp $(DIR_PERIPHERAL)/*.h

dep:
	@$(CPP) -M $(SRCS) $(INCDIR) $(DEFS) > .depend

ifeq (.depend, $(windcard .depend))
include .depend
endif
