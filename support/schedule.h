#ifndef __SCHEDULE_H__
#define __SCHEDULE_H__

// global configuration
#include "config.h"

// system includes
#include <stdint.h>
#include <list>
#include <functional>
#include <vector>

namespace Simulator
{
    class Schedule
    {
        public:
            Schedule();
            ~Schedule();

            void reset(void);
            void process(void);
            void add(int32_t job_time, std::function<void(std::vector<uint32_t>)> job_func, std::vector<uint32_t> params);
            void add_next(std::function<void(std::vector<uint32_t>)> job_func, std::vector<uint32_t> params);

            struct Entry
            {
                uint32_t scheduled_tick;
                std::function<void(std::vector<uint32_t>)> func;
                std::vector<uint32_t> params;
            };
        private:
            std::list<Entry> job_queue;
            uint32_t current_tick;
    };
};

#endif
