#include <iostream>
#include "Communication.hpp"
#include "InputManager.hpp"
#include <spdlog/spdlog.h>
#include "Scheduler.hpp"
#include "Logic.hpp"

int main()
{
    // Create Scheduler and Modules
    Scheduler scheduler;
    InputManager inputManager;
    LogicManager logicManager;

    InputData RwaData;
    InputData outputData;
    SystemState logicState;
    bool status;

    // Task 1: Read and validate input data
    scheduler.addTask(Task(
        "readAndValidate",
        [&]()
        {
            // Print current time
            auto now = std::chrono::steady_clock::now();
            std::cout << "Reading data at "
                      << std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count()
                      << " ms" << std::endl;

            // Test logging
            spdlog::info("Reading data task");

            // Read data
            Communication comm("data/input.json");
            RwaData = comm.readData();

            // Validate input
            status = inputManager.validateInputData(RwaData, outputData);
            std::cout << "Validation Status: " << (status ? "Valid" : "Invalid") << std::endl;
        },
        1000 // every 1 second
        ));

    // Task 2: Apply logic
    scheduler.addTask(Task(
        "applyLogic",
        [&]()
        {
            logicState = logicManager.decideState(outputData);

            std::cout << "Logic Task - system state: "
                      << (logicState == SystemState::ACTIVE      ? "ACTIVE"
                          : logicState == SystemState::IDLE      ? "IDLE"
                          : logicState == SystemState::SLEEP     ? "SLEEP"
                          : logicState == SystemState::LOW_POWER ? "LOW_POWER"
                                                                 : "UNKNOWN")
                      << std::endl;
        },
        1000 // every 1 second
        ));

    // Run Scheduler for 5 seconds
    scheduler.run(5000);

    return 0;
}
