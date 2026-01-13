#pragma once
#include <functional>
#include <string>
#include <vector>
#include <chrono>

/**
 * @brief Represents a single task in the scheduler
 */
struct Task
{
    std::string name;           // Task name
    std::function<void()> func; // Task function
    int period_ms;              // Execution period in milliseconds
    int elapsed_ms;             // Time elapsed since last execution

    Task(const std::string &n, std::function<void()> f, int p)
        : name(n), func(f), period_ms(p), elapsed_ms(0) {}
};

/**
 * @brief Scheduler class to manage tasks
 */
class Scheduler
{
private:
    std::vector<Task> tasks;

public:
    void addTask(const Task &task);
    void run(int duration_ms); // Run the scheduler for a fixed duration (for testing)
};
