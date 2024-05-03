#include "pch.h"
#include "thread_pool.h"

#include <queue>

#include <thread>
#include <condition_variable>
#include <mutex>
#include <iostream>

#define N 10

namespace thread_pool
{
    bool running;
    std::thread threads[N];
    std::queue<job_t> jobs;

    std::condition_variable condition;
    std::mutex mutex;

    void thread_handler();
}

void thread_pool::init()
{
    running = true;
    for (auto& thread : threads) {
        thread = std::thread(thread_handler);
    }
}

void thread_pool::shutdown()
{
    {
        std::unique_lock lock(mutex);
        running = false;
        condition.notify_all();
    }

    for (auto& thread : threads) {
        thread.join();
    }
}

void thread_pool::push(const job_t& job)
{
    std::unique_lock lock(mutex);
    jobs.push(job);
    condition.notify_one();
}

void thread_pool::thread_handler()
{
    while (running)
    {
        job_t job;
        {
            std::unique_lock lock(mutex);

            while (running && jobs.empty()) {
                condition.wait(lock);
            }

            if (jobs.empty()) {
                break;
            }

            job = std::move(jobs.front());
            jobs.pop();
        }
        job(mutex);
    }
}
