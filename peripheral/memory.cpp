
// global configuration
#include "config.h"

// system includes
#include <stdint.h>
#include <vector>

// package includes
#include "memory.h"

namespace Simulator
{
    Memory::Memory(uint32_t _addr_range, uint32_t _access_delay) : Peripheral(_addr_range, _access_delay)
    {
        size_t size = _addr_range >> 2;
        memory = new uint32_t[size];
    }

    Memory::~Memory()
    {
        delete[] memory;
    }

    void Memory::write(uint32_t addr, uint32_t data)
    {
        size_t word_address = addr >> 2;
        memory[word_address] = data;
    }

    uint32_t Memory::read(uint32_t addr)
    {
        size_t word_address = addr >> 2;
        return memory[word_address];
    }

};
