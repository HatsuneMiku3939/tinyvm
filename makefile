CPP = g++

DEFS =
DIR_SUPPORT = support
DIR_CPU = cpu
DIR_PERIPHERAL = peripheral
INCDIR = -I. -I$(DIR_SUPPORT) -I$(DIR_CPU) -I$(DIR_PERIPHERAL)

CPPFLAGS = $(DEFS) $(INCDIR) -g -Wall -std=c++0x
LDFLAGS =

OBJS = support/schedule.o \
	cpu/cpu.o \
	peripheral/bus_interface.o \
	peripheral/peripheral.o \
	peripheral/memory.o

SRCS = $(OBJS:.o=.cpp)

.cpp.o :
	@echo CPP $<
	@$(CPP) $(CPPFLAGS) -c $< -o $@

all : dep simple_vm tag

simple_vm: dep $(OBJS)
	@echo LINK simple_vm
	@$(CPP) $(CPPFLAGS) -c cpu/simple_vm.cpp -o cpu/simple_vm.o
	@$(CPP) $(CPPFLAGS) -c main_simple_vm.cpp -o main_simple_vm.o
	@$(CPP) -o simple_vm.exe $(OBJS) cpu/simple_vm.o main_simple_vm.o $(LDFLAGS)

simple_vm_clean:
	@rm -rf cpu/simple_vm.o

clean : simple_vm_clean
	@rm -f *.exe $(OBJS) .depend tags

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
