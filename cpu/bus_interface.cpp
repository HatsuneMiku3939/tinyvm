// global configuration
#include "config.h"

// system includes
#include <stdint.h>
#include <functional>
#include <vector>

// package includes
#include "bus_interface.h"

namespace Simulator
{
    BusInterface::BusInterface()
    {
    }

    BusInterface::~BusInterface()
    {
    }

    void BusInterface::write(uint32_t addr, uint32_t data)
    {
    }

    uint32_t BusInterface::read(uint32_t addr)
    {
        return 0;
    }
};
