#ifndef __MEMORY_H__
#define __MEMORY_H__

// global configuration
#include "config.h"

// system includes
#include <stdint.h>

// package includes
#include "peripheral.h"

namespace Simulator
{
    class Memory : public Peripheral
    {
        public:
            Memory(uint32_t _addr_range, uint32_t _access_delay);
            virtual ~Memory();

            void write(uint32_t addr, uint32_t data);
            uint32_t read(uint32_t addr);

        private:
            uint32_t *memory;
    };
};

#endif
