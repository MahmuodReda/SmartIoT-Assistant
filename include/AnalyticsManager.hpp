#pragma once
#include "Logic.hpp"

struct AnalyticsReport
{
    int lowPowerCount;
    int activeCount;
    int sleepCount;
    int IDLECount;
    float avgBattery;
};

class AnalyticsManager
{
public:
    void update(SystemState state, const InputData &data);
    AnalyticsReport getReport() const;

private:
    int lowPowerCounter = 0;
    int activeCounter = 0;
    int sleepCounter = 0;
    int IDLECounter = 0;
    float batterySum = 0.0f;
    int samples = 0;
};
