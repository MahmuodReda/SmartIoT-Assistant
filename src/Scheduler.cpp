#include "Scheduler.hpp"
#include <iostream>
#include <thread>

void Scheduler::addTask(const Task &task)
{
    tasks.push_back(task);
}
void Scheduler::run(int duration_ms)
{
    using clock = std::chrono::steady_clock;
    using ms = std::chrono::milliseconds;

    auto start = clock::now();
    auto next_tick = start;

    while (true)
    {
        auto now = clock::now();
        if (std::chrono::duration_cast<ms>(now - start).count() >= duration_ms)
            break;

        for (auto &task : tasks)
        {
            task.elapsed_ms += 10;

            if (task.elapsed_ms >= task.period_ms)
            {
                task.func();
                task.elapsed_ms = 0;
            }
        }

        next_tick += ms(10);
        std::this_thread::sleep_until(next_tick);
    }
}
