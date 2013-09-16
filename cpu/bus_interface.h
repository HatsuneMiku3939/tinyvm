#ifndef __BUS_INTERFACE_H__
#define __BUS_INTERFACE_H__

// global configuration
#include "config.h"

// system includes
#include <stdint.h>

// package includes

namespace Simulator
{
    class BusInterface
    {
        public:
            BusInterface();
            ~BusInterface();

            void write(uint32_t addr, uint32_t data);
            uint32_t read(uint32_t addr);

        private:
    };
};

#endif
