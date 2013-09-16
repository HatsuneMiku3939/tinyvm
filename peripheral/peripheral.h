#ifndef __PERIPHERAL_H__
#define __PERIPHERAL_H__

// global configuration
#include "config.h"

// system includes
#include <stdint.h>

// package includes

namespace Simulator
{
    class Peripheral
    {
        public:
            Peripheral(uint32_t _addr_range);
            virtual ~Peripheral();

            virtual void write(uint32_t addr, uint32_t data) = 0;
            virtual uint32_t read(uint32_t addr) = 0;

            uint32_t get_addr_range(void);

        protected:
            uint32_t addr_range;
    };
};

#endif
