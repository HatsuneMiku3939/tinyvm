#ifndef __CPU_H__
#define __CPU_H__

// global configuration
#include "config.h"

// system includes
#include <vector>

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
            void fetch(std::vector<uint32_t> params);
            void decode(std::vector<uint32_t> params);

        public:
            void halt(std::vector<uint32_t> params);
            void load(std::vector<uint32_t> params);
            void add(std::vector<uint32_t> params);
            void sub(std::vector<uint32_t> params);
            void print(std::vector<uint32_t> params);

        private:
            int regs[16];

        private:
            Schedule *schedule;
            BusInterface *inst_bus;
            BusInterface *data_bus;
    };
};

#endif
