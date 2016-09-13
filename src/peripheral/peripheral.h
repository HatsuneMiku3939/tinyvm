#ifndef __PERIPHERAL_H__
#define __PERIPHERAL_H__

// global configuration
#include "config.h"

// system includes

// package includes

namespace Simulator
{
    class Peripheral
    {
        public:
            Peripheral(uint32_t _addr_range, uint32_t _access_delay);
            virtual ~Peripheral();

            virtual void write(uint32_t addr, uint32_t data) = 0;
            virtual uint32_t read(uint32_t addr) = 0;

            uint32_t get_addr_range(void);
            uint32_t get_access_delay(void);

        protected:
            uint32_t addr_range;
            uint32_t access_delay;
    };
};

#endif
