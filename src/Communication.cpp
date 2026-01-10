#include <iostream>
#include <fstream>
#include "Communication.hpp"
#include "json.hpp" // nlohmann JSON

using json = nlohmann::json;

void Communication_Test()
{
    std::ifstream input_file("data/input.json");

    if (!input_file.is_open())
    {
        std::cerr << "[COMM] Failed to open input.json\n";
        return;
    }
    json data;
    try
    {

        input_file >> data;
    }
    catch (...)
    {
        std::cerr << "[COMM] Invalid JSON format\n";
        return;
    }

    int battery_level = data["battery_level"];
    bool presence = data["presence"];
    int steps = data["steps"];

    std::cout << "[COMM] battery_level = " << battery_level << "\n";
    std::cout << "[COMM] presence      = " << presence << "\n";
    std::cout << "[COMM] steps         = " << steps << "\n";

    input_file.close();
}
