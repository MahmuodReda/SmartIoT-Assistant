#include "Logic.hpp"

SystemState LogicManager::decideState(const InputData &data)
{
    // Rule 1: Low battery → LOW_POWER
    if (data.battery_level >= 0 && data.battery_level < 20)
        return SystemState::LOW_POWER;

    // Rule 2: No presence + no activity → SLEEP
    if (!data.presence && data.steps == 0)
        return SystemState::SLEEP;

    // Rule 3: Presence or activity → ACTIVE
    if (data.presence || data.steps > 0)
        return SystemState::ACTIVE;

    // Default
    return SystemState::IDLE;
}
