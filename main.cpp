#include <iostream>
#include "Communication.hpp"
#include "InputManager.hpp"
#include <spdlog/spdlog.h>
#include "Scheduler.hpp"
int main()
{

    Scheduler scheduler;
    InputData RwaData;
    InputManager inputManager;
    InputData outputData;
    bool status;
    scheduler.addTask(Task("readData", [&]()
                           {
                             auto now = std::chrono::steady_clock::now();
                            
                             std::cout << "Reading data at "
                                       << std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count()
                                       << " ms" << std::endl;
            spdlog::info("Test");
    Communication comm("data/input.json");
    RwaData = comm.readData();
    status = inputManager.validateInputData(RwaData, outputData);
    std::cout << "Overall Input Data Validation Status: " << (status ? "Valid" : "Invalid") << std::endl; }, 1000));

    // Run scheduler for 5 seconds
    scheduler.run(10000);
    return 0;
}
