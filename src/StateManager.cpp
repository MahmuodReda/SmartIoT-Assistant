#include "StateManager.hpp"

void StateManager::updateState(SystemState newState)
{
    if (newState != currentState)
    {
        std::cout << "[STATE MANAGER] Transition: "
                  << stateToString(currentState)
                  << " -> "
                  << stateToString(newState)
                  << std::endl;

        currentState = newState;

        // Perform action on new state
        performAction(currentState);
    }
}

void StateManager::performAction(SystemState state)
{
    switch (state)
    {
    case SystemState::ACTIVE:
        std::cout << "[ACTION] System is ACTIVE\n";
        break;
    case SystemState::IDLE:
        std::cout << "[ACTION] System is IDLE\n";
        break;
    case SystemState::SLEEP:
        std::cout << "[ACTION] System is in SLEEP mode\n";
        break;
    case SystemState::LOW_POWER:
        std::cout << "[ACTION] LOW POWER mode - saving energy!\n";
        break;
    default:
        break;
    }
}

const char *StateManager::stateToString(SystemState state)
{
    switch (state)
    {
    case SystemState::ACTIVE:
        return "ACTIVE";
    case SystemState::IDLE:
        return "IDLE";
    case SystemState::SLEEP:
        return "SLEEP";
    case SystemState::LOW_POWER:
        return "LOW_POWER";
    default:
        return "UNKNOWN";
    }
}
