#pragma once

#include <string>
#include <fstream>
#include "InputData.hpp"

/**
 * @brief Communication class to handle reading data from a JSON file.
 *
 */
class Communication
{
private:
    std::string filename_;
    std::ifstream input_file;

public:
    Communication(const std::string &filename);
    InputData readData();
    ~Communication() = default;
};