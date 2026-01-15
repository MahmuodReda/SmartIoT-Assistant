#pragma once
#include "InputManager.hpp"
#include <random>

/**
 * @brief DataSimulator generates dynamic input data for integration testing
 */
class DataSimulator
{
public:
    DataSimulator()
        : battery(100), steps(0), presence(true),
          rng(std::random_device{}()), dist(0, 1) {}

    InputData getNext()
    {
        // Decrease battery slowly
        battery -= 1;
        if (battery < 0)
            battery = 0;

        // Toggle presence randomly
        presence = dist(rng) > 0.5;

        // Increase steps
        steps += 100;

        InputData data;
        data.battery_level = battery;
        data.presence = presence;
        data.steps = steps;
        return data;
    }

private:
    int battery;
    int steps;
    bool presence;

    std::mt19937 rng;
    std::uniform_real_distribution<float> dist;
};
