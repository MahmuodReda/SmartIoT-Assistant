#pragma once

#include "InputData.hpp"

class InputManager

{
public:
    bool validateInputData(const InputData &data, InputData &outputData);
};