#include "Communication.hpp"
#include "json.hpp" // nlohmann JSON
#include <iostream>

using json = nlohmann::json;

/**
 * @brief Construct a new Communication:: Communication object
 *
 * @param filename The input filename
 */
Communication::Communication(const std::string &filename)
    : filename_(filename), input_file(filename)
{
    if (!input_file.is_open())
    {
        std::cerr << "[COMM] Failed to open input.json\n";
        return;
    }
}
/**
 * @brief Read data from the input file.
 *
 */
void Communication::readData()
{

    if (!input_file.is_open())
    {
        std::cerr << "[COMM] Failed to open " << filename_ << "\n";
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
}

/* ~Communication()
 {
     input_file.close();
 }

 */

// i committed this line because already closed infstream in destructor

/*    ~std::ifstream()
{
    close();
}
    */