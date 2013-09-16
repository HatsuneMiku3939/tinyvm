// global configuration
#include "config.h"

// system includes
#include <stdint.h>
#include <functional>
#include <vector>
#include <algorithm>

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
        std::vector<Entry>::iterator it;
        it = find_peripheral(addr);

        if(it == peripherals.end())
        {
            // TODO, bus exception
        }

        it->peripheral->write(addr - it->start_addr, data);
    }

    uint32_t BusInterface::read(uint32_t addr)
    {
        std::vector<Entry>::iterator it;
        it = find_peripheral(addr);

        if(it == peripherals.end())
        {
            // TODO, bus exception
        }

        return it->peripheral->read(addr - it->start_addr);
    }

    void BusInterface::add_peripheral(uint32_t start_addr, Peripheral *peripheral)
    {
        std::vector<Entry>::iterator it;
        it = find_peripheral(start_addr);

        if(it != peripherals.end())
        {
            // TODO, raise program error
            return;
        }

        Entry tmp;
        tmp.start_addr = start_addr;
        tmp.addr_range = peripheral->get_addr_range();
        tmp.peripheral = peripheral;

        peripherals.push_back(tmp);
    }

    std::vector<BusInterface::Entry>::iterator BusInterface::find_peripheral(uint32_t addr)
    {
        std::vector<Entry>::iterator it;
        it = find_if(peripherals.begin(), peripherals.end(), [addr](Entry e) -> bool
            {
                // TODO, refectoring is required, more compact condition
                return (e.start_addr >= addr) && (e.start_addr + e.addr_range >= addr);
            }
        );

        return it;
    }
};
