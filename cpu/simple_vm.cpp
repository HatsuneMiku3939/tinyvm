// global configuration
#include "config.h"

// system includes
#include <stdint.h>
#include <functional>
#include <vector>
#include <iostream>
#include <cstring>

// package includes
#include "simple_vm.h"
#include "schedule.h"
#include "bus_interface.h"

// local macro
#define PC  (15)

#define HALT    (0)
#define LOAD    (1)
#define ADD     (2)
#define SUB     (3)
#define PRINT   (4)

#define FIELD_MSB(field) field[0]
#define FIELD_LSB(field) field[1]
#define DECODE(instr, field) (instr & ((1 << (FIELD_MSB(field))+1) - 1)) >> FIELD_LSB(field)

namespace Simulator
{
    SimpleVM::SimpleVM(Schedule *_schedule, BusInterface *_inst_bus, BusInterface *_data_bus) : CPU(_schedule, _inst_bus, _data_bus)
    {
        std::memset(regs, 0, sizeof(regs));
    }

    SimpleVM::~SimpleVM()
    {
    }

    void SimpleVM::fetch(std::vector<uint32_t> params)
    {
        using namespace std;
        using namespace std::placeholders;

        uint32_t pc = regs[PC];
        uint32_t inst = inst_bus->read(pc);
        uint32_t bus_delay = inst_bus->get_access_delay(pc);

        schedule->add(bus_delay, bind(mem_fn(&CPU::decode), this, _1), vector<uint32_t>({inst}));
        regs[PC] += 4;
    }

    void SimpleVM::decode(std::vector<uint32_t> params)
    {
        using namespace std;
        using namespace std::placeholders;

        static const int field_instr[] = {15, 12};
        static const int field_reg1[] = {11, 8};
        static const int field_reg2[] = {7, 4};
        static const int field_reg3[] = {3, 0};
        static const int field_imm[] = {7, 0};

        int inst = DECODE(params[0], field_instr);
        int operand1 = DECODE(params[0], field_reg1);
        int operand2 = DECODE(params[0], field_reg2);
        int operand3 = DECODE(params[0], field_reg3);
        int imm = DECODE(params[0], field_imm);

        bool stoped = false;
        int process_delay;

        switch(inst)
        {
        case HALT:
            stoped = true;
            break;

        case LOAD:
            process_delay = 1;
            schedule->add_next(bind(mem_fn(&SimpleVM::load), this, _1), vector<uint32_t>({operand1, imm}));
            break;

        case ADD:
            process_delay = 1;
            schedule->add_next(bind(mem_fn(&SimpleVM::add), this, _1), vector<uint32_t>({operand1, operand2, operand3}));
            break;

        case SUB:
            process_delay = 1;
            schedule->add_next(bind(mem_fn(&SimpleVM::sub), this, _1), vector<uint32_t>({operand1, operand2, operand3}));
            break;

        case PRINT:
            process_delay = 10;
            schedule->add(10,bind(mem_fn(&SimpleVM::print), this, _1), vector<uint32_t>({operand1}));
            break;

        default:
            stoped = true;
            break;
        }


        if(!stoped)
        {
            schedule->add(process_delay + 1, bind(mem_fn(&SimpleVM::fetch), this, _1), vector<uint32_t>({}));
        }
    }

    void SimpleVM::load(std::vector<uint32_t> params)
    {
        regs[params[0]] = params[1];
    }

    void SimpleVM::add(std::vector<uint32_t> params)
    {
        regs[params[0]] = regs[params[1]] + regs[params[2]];
    }

    void SimpleVM::sub(std::vector<uint32_t> params)
    {
        regs[params[0]] = regs[params[1]] - regs[params[2]];
    }

    void SimpleVM::print(std::vector<uint32_t> params)
    {
        std::cout << regs[params[0]] << std::endl;
    }
};
