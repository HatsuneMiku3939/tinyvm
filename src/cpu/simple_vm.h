#ifndef __SIMPLE_VM_H__
#define __SIMPLE_VM_H__

// global configuration
#include "config.h"

// system includes
#include <vector>

// package includes
#include "cpu.h"
#include "bus_interface.h"
#include "schedule.h"

namespace Simulator
{
    class SimpleVM : public CPU
    {
        public:
            SimpleVM(Schedule *_schedule, BusInterface *_inst_bus, BusInterface *_data_bus);
            ~SimpleVM();

        public:
            void fetch(std::vector<uint32_t> params);
            void decode(std::vector<uint32_t> params);

        public:
            int regs[16];

            void halt(std::vector<uint32_t> params);
            void load(std::vector<uint32_t> params);
            void add(std::vector<uint32_t> params);
            void sub(std::vector<uint32_t> params);
            void print(std::vector<uint32_t> params);
    };
};

#endif
