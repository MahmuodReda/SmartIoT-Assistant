#include "OutputManager.hpp"
#include <iostream>

void OutputManager::execute(SystemState state)
{
    switch (state)
    {
    case SystemState::ACTIVE:
        std::cout << "[OUTPUT] System ACTIVE: Full functionality enabled\n";
        break;

    case SystemState::IDLE:
        std::cout << "[OUTPUT] System IDLE: Reduced activity\n";
        break;

    case SystemState::SLEEP:
        std::cout << "[OUTPUT] System SLEEP: Most components off\n";
        break;

    case SystemState::LOW_POWER:
        std::cout << "[OUTPUT] System LOW_POWER: Energy saving mode\n";
        break;

    default:
        std::cout << "[OUTPUT] Unknown system state\n";
        break;
    }
}
