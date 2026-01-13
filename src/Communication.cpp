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
InputData Communication::readData()
{

    InputData inputData{
        inputData.battery_level = -1,
        inputData.presence = false,
        inputData.steps = 0};

    if (!input_file.is_open())
    {
        std::cerr << "[COMM] Failed to open " << filename_ << "\n";
        return inputData;
    }
    json data;
    try
    {

        input_file >> data;
    }
    catch (...)
    {
        std::cerr << "[COMM] Invalid JSON format\n";
        return inputData;
    }

    inputData.battery_level = data["battery_level"];
    inputData.presence = data["presence"];
    inputData.steps = data["steps"];
    input_file.clear();                 // clear EOF flag
    input_file.seekg(0, std::ios::beg); // rewind to beginning for next read

    return inputData;
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