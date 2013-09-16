#ifndef __BUS_INTERFACE_H__
#define __BUS_INTERFACE_H__

// global configuration
#include "config.h"

// system includes
#include <stdint.h>
#include <vector>

// package includes
#include "peripheral.h"

namespace Simulator
{
    class BusInterface
    {
        public:
            BusInterface();
            virtual ~BusInterface();

            void write(uint32_t addr, uint32_t data);
            uint32_t read(uint32_t addr);

            void add_peripheral(uint32_t start_addr, Peripheral *peripheral);

        private:
            struct Entry
            {
                uint32_t start_addr;
                uint32_t addr_range;
                Peripheral *peripheral;
            };

            std::vector<Entry> peripherals;
            std::vector<Entry>::iterator find_peripheral(uint32_t addr);
    };
};

#endif
