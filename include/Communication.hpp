#pragma once
#include <string>
#include <fstream>
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
    void readData();
    ~Communication() = default;
};