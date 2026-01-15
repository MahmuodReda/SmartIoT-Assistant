#include <iostream>
#include <spdlog/spdlog.h>
#include "AnalyticsManager.hpp"
#include "Scheduler.hpp"
#include "Communication.hpp"
#include "InputManager.hpp"
#include "Logic.hpp"
#include "StateManager.hpp"

int main()
{
    Scheduler scheduler;

    Communication comm("data/input.json"); // Created ONCE
    InputManager inputManager;
    LogicManager logicManager;
    StateManager stateManager;
    AnalyticsManager analytics;
    InputData rawData{};
    InputData validatedData{};
    bool isValid = false;
    SystemState decision = SystemState::SLEEP;

    // Task 1: Read and validate input data
    scheduler.addTask(Task(
        "readAndValidate",
        [&]()
        {
            spdlog::info("Task: Read & Validate");

            rawData = comm.readData();
            isValid = inputManager.validateInputData(rawData, validatedData);

            std::cout << "[MAIN] Validation result: "
                      << (isValid ? "VALID" : "INVALID")
                      << std::endl;
        },
        1000));

    // Task 2: Apply logic and update state (only if data is valid)
    scheduler.addTask(Task(
        "logicAndState",
        [&]()
        {
            if (!isValid)
            {
                spdlog::warn("Skipping logic: invalid input data");
                return;
            }

            decision = logicManager.decideState(validatedData);

            std::cout << "[MAIN] Decision: "
                      << stateToString(decision)
                      << std::endl;

            stateManager.updateState(decision);
        },
        1000));
    // Task 3: Analytics update
    scheduler.addTask(Task(
        "analytics",
        [&]()
        {
            analytics.update(
                decision,
                validatedData);
            AnalyticsReport report = analytics.getReport();
            std::cout << "Analytics counters = " << std::endl
                      << "  LOW_POWER: " << report.lowPowerCount << std::endl
                      << "  ACTIVE:    " << report.activeCount << std::endl
                      << "  SLEEP:     " << report.sleepCount << std::endl
                      << "  IDLE:      " << report.IDLECount << std::endl
                      << "  Avg Battery: " << report.avgBattery << std::endl;
        },
        5000));

    // Run scheduler for 10 seconds
    scheduler.run(5000);

    return 0;
}
