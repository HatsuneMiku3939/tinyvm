// global configuration
#include "config.h"

// system includes
#include <stdint.h>

// package includes
#include "peripheral.h"

namespace Simulator
{
    Peripheral::Peripheral(uint32_t _addr_range)
    {
        addr_range = _addr_range;
    }

    Peripheral::~Peripheral()
    {
        // do nothing
    }

    uint32_t Peripheral::get_addr_range(void)
    {
        return addr_range;
    }
};
