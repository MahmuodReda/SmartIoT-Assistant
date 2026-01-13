#pragma once
#include "Logic.hpp"
#include <iostream>
#include "OutputManager.hpp"

class StateManager
{
private:
    SystemState currentState;
    OutputManager outputManager;

public:
    StateManager() : currentState(SystemState::SLEEP) {}

    void updateState(SystemState newState);
};
