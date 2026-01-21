/**
 * @file AnalyticsManager.cpp
 * @author Mahmoud Reda
 * @brief
 * @version 0.1
 * @date 2026-01-21
 *
 * @copyright Copyright (c) 2026
 *
 */
#include "AnalyticsManager.hpp"
/**
 * @brief Updates the analytics manager with new system state and input data.
 *
 * @param state
 * @param data
 */
void AnalyticsManager::update(SystemState state, const InputData &data)
{
    samples++;
    batterySum += data.battery_level;

    if (state == SystemState::LOW_POWER)
    {
        lowPowerCounter++;
    }
    else if (state == SystemState::ACTIVE)
    {
        activeCounter++;
    }
    else if (state == SystemState::SLEEP)
    {
        sleepCounter++;
    }
    else if (state == SystemState::IDLE)
    {
        IDLECounter++;
    }
}
/**
 * @brief Returns the current analytics report.
 *
 * @return AnalyticsReport
 */
AnalyticsReport AnalyticsManager::getReport() const
{
    AnalyticsReport report;
    report.lowPowerCount = lowPowerCounter;
    report.activeCount = activeCounter;
    report.sleepCount = sleepCounter;
    report.IDLECount = IDLECounter;
    report.avgBattery = (samples > 0) ? (batterySum / samples) : 0.0f;
    return report;
}
