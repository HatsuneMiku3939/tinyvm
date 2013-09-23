// global configuration
#include "config.h"

// system includes
#include <stdint.h>
#include <signal.h>
#include <iostream>
#include <cstdlib>
#include <functional>
#include <vector>

// package includes
#include "main_simple_vm.h"

#include "simple_vm.h"
#include "memory.h"
#include "schedule.h"
#include "bus_interface.h"

int main(int argc, char **argv)
{
    using namespace std;
    using namespace std::placeholders;
    using namespace Simulator;

    // portablity issue
    signal(SIGINT, sigint_handler);

    Schedule schedule;
    Memory memory(1024, 5);
    BusInterface bus;

    bus.add_peripheral(0x00000000, &memory);
    SimpleVM cpu(&schedule, &bus, &bus);

    memory.write(0x0000, 0x00001123);     // LOAD  1, 35
    memory.write(0x0004, 0x000012c8);     // LOAD  2, 200
    memory.write(0x0008, 0x00003012);     // SUB   0, 1, 2
    memory.write(0x000C, 0x00002312);     // ADD   3, 1, 2
    memory.write(0x0010, 0x00004000);     // PRINT 1
    memory.write(0x0014, 0x00004300);     // PRINT 3
    memory.write(0x0018, 0x00000000);     // HALT

    schedule.add_next(bind(mem_fn(&SimpleVM::fetch), &cpu, _1), vector<uint32_t>({}));

    while(true)
    {
        schedule.process();
    }

    return 0;
}

void sigint_handler(int param)
{
    std::exit(0);
}
