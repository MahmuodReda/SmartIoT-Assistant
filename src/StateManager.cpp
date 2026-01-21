/**
 * @file StateManager.cpp
 * @author Mahmoud Reda
 * @brief
 * @version 0.1
 * @date 2026-01-21
 *
 * @copyright Copyright (c) 2026
 *
 */
#include "StateManager.hpp"
/**
 * @brief Updates the current system state.
 *
 * @param newState
 */
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
