// global configuration
#include "config.h"

// system includes
#include <stdint.h>
#include <functional>
#include <vector>

// package includes
#include "cpu.h"
#include "schedule.h"
#include "bus_interface.h"

namespace Simulator
{
    CPU::CPU(Schedule *_schedule, BusInterface *inst_bus, BusInterface *data_bus)
    {
        schedule = _schedule;
    }

    CPU::~CPU()
    {
    }
};
