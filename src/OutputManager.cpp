#include "OutputManager.hpp"
#include <iostream>

void OutputManager::printState(SystemState state)
{
    std::cout << "[OUTPUT] Current State: ";

    switch (state)
    {
    case SystemState::ACTIVE:
        std::cout << "ACTIVE - Full functionality enabled";
        break;

    case SystemState::IDLE:
        std::cout << "IDLE - Reduced activity";
        break;

    case SystemState::SLEEP:
        std::cout << "SLEEP - Most components off";
        break;

    case SystemState::LOW_POWER:
        std::cout << "LOW_POWER - Energy saving mode";
        break;

    default:
        std::cout << "UNKNOWN";
        break;
    }

    std::cout << std::endl;
}

void OutputManager::printAnalytics(const AnalyticsReport &report)
{
    std::cout << "\n[ANALYTICS REPORT]\n";
    std::cout << "  ACTIVE Count    : " << report.activeCount << "\n";
    std::cout << "  IDLE Count      : " << report.IDLECount << "\n";
    std::cout << "  SLEEP Count     : " << report.sleepCount << "\n";
    std::cout << "  LOW_POWER Count : " << report.lowPowerCount << "\n";
    std::cout << "  Avg Battery     : " << report.avgBattery << "\n";
    std::cout << "-----------------------------\n";
}
