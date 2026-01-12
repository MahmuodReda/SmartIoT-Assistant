#include "InputManager.hpp"
#include "Communication.hpp"
#include <iostream>

bool InputManager::validateInputData(const InputData &data, InputData &outputData)
{
    bool isValid = true;

    if (data.battery_level < 0 || data.battery_level > 100)
    {

        std::cerr << "[INPUT MANAGER] Invalid battery level: " << data.battery_level << "\n";
        isValid = false;
        outputData.battery_level = -1; // Indicate invalid battery level
    }
    else
    {
        outputData.battery_level = data.battery_level;
        std::cout << "[INPUT MANAGER] Valid battery level: " << data.battery_level << "\n";
    }
    if (data.presence != true && data.presence != false)
    {
        std::cerr << "[INPUT MANAGER] Invalid presence value: " << data.presence << "\n";
        isValid = false;
        outputData.presence = false; // Default to false on invalid input
    }
    else
    {
        outputData.presence = data.presence;
        std::cout << "[INPUT MANAGER] Valid presence value: " << data.presence << "\n";
    }
    if (data.steps < 0)
    {
        std::cerr << "[INPUT MANAGER] Invalid steps count: " << data.steps << "\n";
        isValid = false;
        outputData.steps = 0; // Default to 0 on invalid input
    }
    else
    {
        outputData.steps = data.steps;
        std::cout << "[INPUT MANAGER] Valid steps count: " << data.steps << "\n";
    }
    return isValid;
};
