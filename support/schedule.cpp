// global configuration
#include "config.h"

// system includes
#include <stdint.h>
#include <list>
#include <algorithm>

// package includes
#include "schedule.h"

namespace Simulator
{
    Schedule::Schedule()
    {
        reset();
    }

    Schedule::~Schedule()
    {
        // do nothing
    }

    void Schedule::reset(void)
    {
        job_queue.clear();
        current_tick = 0;
    }

    void Schedule::add(int32_t job_time, std::function<void(std::vector<uint32_t>)> job_func, std::vector<uint32_t> params)
    {
        Entry job;

        job.scheduled_tick = current_tick + job_time;
        job.func = job_func;
        job.params = params;

        job_queue.push_back(job);
    }

    void Schedule::add_next(std::function<void(std::vector<uint32_t>)> job_func, std::vector<uint32_t> params)
    {
        add(1, job_func, params);
    }

    void Schedule::process(void)
    {
        current_tick += 1;

        std::list<Entry>::iterator it;
        it = job_queue.begin();

        while(it != job_queue.end())
        {
            if(current_tick >= it->scheduled_tick)
            {
                it->func(it->params);
            }
            it++;
        }

        job_queue.remove_if([this](Entry e) -> bool
            {
                return this->current_tick >= e.scheduled_tick;
            }
        );
    }
};
