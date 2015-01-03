// global configuration
#include "config.h"

// system includes

// package includes
#include "peripheral.h"

namespace Simulator
{
    Peripheral::Peripheral(uint32_t _addr_range, uint32_t _access_delay)
    {
        addr_range = _addr_range;
        access_delay = _access_delay;
    }

    Peripheral::~Peripheral()
    {
        // do nothing
    }

    uint32_t Peripheral::get_addr_range(void)
    {
        return addr_range;
    }

    uint32_t Peripheral::get_access_delay(void)
    {
        return access_delay;
    }
};
