#include "InputSystem.h"

#include <iostream>

float InputSystem::GetLeftTriggerPressure() const
{
    std::cout << "Selected input system does not support triggers\n";
    return 0.0f;
}

float InputSystem::GetRightTriggerPressure() const
{
    std::cout << "Selected input system does not support triggers\n";
    return 0.0f;
}

std::pair<float, float> InputSystem::GetLeftStickValues() const
{
    std::cout << "Selected input system does not support analogue sticks\n";
    return std::pair<float, float>{};
}

std::pair<float, float> InputSystem::GetRightStickValues() const
{
    std::cout << "Selected input system does not support analogue sticks\n";
    return std::pair<float, float>{};
}

int InputSystem::GetConnectedControllers() const
{
    std::cout << "Selected input system does not support multiple input devices\n";
    return 0;
}
