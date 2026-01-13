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
    InputManager inputManager;
    LogicManager logicManager;
    StateManager stateManager;

    InputData rawData;
    InputData validatedData;
    bool status;

    // Task 1: Read and validate input data
    scheduler.addTask(Task(
        "readAndValidate",
        [&]()
        {
            spdlog::info("Reading data task");

            Communication comm("data/input.json");
            rawData = comm.readData();

            status = inputManager.validateInputData(rawData, validatedData);
            std::cout << "Validation Status: " << (status ? "Valid" : "Invalid") << std::endl;
        },
        1000 // every 1 second
        ));

    // Task 2: Apply logic and update state
    scheduler.addTask(Task(
        "logicAndState",
        [&]()
        {
            SystemState decision = logicManager.decideState(validatedData);
            stateManager.updateState(decision);
        },
        1000 // every 1 second
        ));

    // Run scheduler for 10 seconds
    scheduler.run(10000);

    return 0;
}
