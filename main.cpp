#include <iostream>
#include "Communication.hpp"
#include "InputManager.hpp"
int main()
{
    Communication comm("data/input.json"); // Specify the path to your JSON file
    InputData RwaData = comm.readData();   // Read and process the data
    InputManager inputManager;
    InputData outputData;
    bool status = inputManager.validateInputData(RwaData, outputData);
    std::cout << "outputData.battery_level: " << outputData.battery_level << std::endl;
    std::cout << "outputData.presence: " << outputData.presence << std::endl;
    std::cout << "outputData.steps: " << outputData.steps << std::endl;

    std::cout << "Overall Input Data Validation Status: " << (status ? "Valid" : "Invalid") << std::endl;

    return 0;
}
