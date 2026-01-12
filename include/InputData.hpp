#pragma once

/**
 * @brief Structured input data after Communication stage
 */
struct InputData
{
    int battery_level; // expected: 0 - 100
    bool presence;
    int steps; // expected: >= 0
};