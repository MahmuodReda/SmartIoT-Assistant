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

/**
 * @brief Convert SystemState enum to string
 */
inline const char *stateToString(SystemState state)
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