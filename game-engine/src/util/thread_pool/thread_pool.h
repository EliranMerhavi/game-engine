#pragma once

#include "jobs.h"

namespace thread_pool
{
    void init();
    void shutdown();
    void push(const job_t& job);
}
