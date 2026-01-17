#include <iostream>
#include <spdlog/spdlog.h>
#include "AnalyticsManager.hpp"
#include "Scheduler.hpp"
#include "Communication.hpp"
#include "InputManager.hpp"
#include "Logic.hpp"
#include "StateManager.hpp"
#include "DataSimulator.hpp"
#include "HttpServer.hpp"
#include "thread"

void allfun()
{
}
int main()
{

    HttpServer httpServer;
    httpServer.start();

    OutputManager output;
    Scheduler scheduler;

    InputData rawData{};

    InputManager inputManager;
    LogicManager logicManager;
    StateManager stateManager;
    AnalyticsManager analytics;

    InputData validatedData{};
    SystemState decision = SystemState::SLEEP;
    bool isValid = false;
    DataSimulator simulator;

    // Task 1: Read and validate input data
    scheduler.addTask(Task(
        "readAndValidate",
        [&]()
        {
            Communication comm("D:\\Mahmood_Reda\\SmartIoT-Assistant\\data\\input.json"); // Created ONCE

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

            output.printState(decision);
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
            output.printAnalytics(report);
        },
        9999));

    // Run scheduler for 10 seconds

    scheduler.run(10000);
    allfun();

    return 0;
}
