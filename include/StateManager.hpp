#pragma once
#include "Logic.hpp"
#include <iostream>

/**
 * @brief StateManager handles current system state and transitions
 */
class StateManager
{
private:
    SystemState currentState;

public:
    StateManager() : currentState(SystemState::SLEEP) {} // start in SLEEP

    SystemState getState() const { return currentState; }

    /**
     * @brief Update state if different from current
     * @param newState
     */
    void updateState(SystemState newState);

private:
    void performAction(SystemState state);        // execute action on new state
    const char *stateToString(SystemState state); // helper for printing
};
