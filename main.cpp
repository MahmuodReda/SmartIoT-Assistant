#include <iostream>
#include "Communication.hpp"

int main()
{
    Communication comm("data/input.json"); // Specify the path to your JSON file
    comm.readData();                       // Read and process the data

    return 0;
}
