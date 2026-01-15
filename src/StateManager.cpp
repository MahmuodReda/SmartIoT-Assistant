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
        }
}
