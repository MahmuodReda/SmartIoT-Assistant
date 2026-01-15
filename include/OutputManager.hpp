#pragma once
#include "Logic.hpp"
#include "AnalyticsManager.hpp"

/**
 * @brief OutputManager handles all system outputs
 *        (console, logs, external interfaces later)
 */
class OutputManager
{
public:
    void printState(SystemState state);
    void printAnalytics(const AnalyticsReport &report);
};
