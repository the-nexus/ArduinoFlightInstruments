#pragma once

#define ARDUINO_LOW = 0;
#define ARDUINO_HIGH = 255;

enum class ArduinoCommandType
{
    Invalid = 0,
    Handshake = 1,
    Acknowledge = 2,
    UpdateInputData = 3,
    UpdateOutputData = 4
};

enum class ArduinoComponentType
{
    LED = 0,
    Button = 1,
    Switch = 2
};
