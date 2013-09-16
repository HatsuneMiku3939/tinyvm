#ifndef __CPU_H__
#define __CPU_H__

// global configuration
#include "config.h"

// system includes

// package includes
#include "bus_interface.h"
#include "schedule.h"

namespace Simulator
{
    class CPU
    {
        public:
            CPU(Schedule *_schedule, BusInterface *_inst_bus, BusInterface *_data_bus);
            ~CPU();

        public:

        private:
            Schedule *schedule;
            BusInterface *inst_bus;
            BusInterface *data_bus;
    };
};

#endif
