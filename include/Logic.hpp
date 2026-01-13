#pragma once

#include "InputData.hpp"

enum class SystemState
{
    ACTIVE,
    IDLE,
    SLEEP,
    LOW_POWER
};

class LogicManager
{
public:
    SystemState decideState(const InputData &data);
};
