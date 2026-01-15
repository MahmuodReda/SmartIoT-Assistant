#include "AnalyticsManager.hpp"
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
