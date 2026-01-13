#pragma once
#include "Logic.hpp"

/**
 * @brief OutputManager executes actions based on system state
 */
class OutputManager
{
public:
    OutputManager() = default;

    /**
     * @brief Execute output action according to current state
     * @param state Current system state
     */
    void execute(SystemState state);
};
