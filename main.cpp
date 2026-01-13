#include <iostream>
#include <spdlog/spdlog.h>

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

    InputData rawData{};
    InputData validatedData{};
    bool isValid = false;

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

            SystemState decision = logicManager.decideState(validatedData);

            std::cout << "[MAIN] Decision: "
                      << stateToString(decision)
                      << std::endl;

            stateManager.updateState(decision);
        },
        1000));

    // Run scheduler for 10 seconds
    scheduler.run(5000);

    return 0;
}
