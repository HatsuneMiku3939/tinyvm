CPP = g++

DEFS =
DIR_SUPPORT = support
DIR_CPU = cpu
INCDIR = -I. -I$(DIR_SUPPORT) -T$(DIR_CPU)

CPPFLAGS = $(DEFS) $(INCDIR) -g -Wall -std=c++0x
LDFLAGS =

PROG = test

OBJS = main.o \
	support/schedule.o \
	cpu/cpu.o \
	cpu/bus_interface.o \
	pheri/memory.o

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

dep:
	@$(CPP) -M $(SRCS) $(INCDIR) $(DEFS) > .depend

ifeq (.depend, $(windcard .depend))
include .depend
endif
