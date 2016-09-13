// global configuration
#include "config.h"

// system includes
#include <functional>
#include <vector>
#include <iostream>
#include <cstring>

// package includes
#include "cpu.h"
#include "schedule.h"
#include "bus_interface.h"

namespace Simulator
{
    CPU::CPU(Schedule *_schedule, BusInterface *_inst_bus, BusInterface *_data_bus)
    {
        schedule = _schedule;
        inst_bus = _inst_bus;
        data_bus = _data_bus;
    }

    CPU::~CPU()
    {
    }
};
