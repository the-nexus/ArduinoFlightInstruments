#pragma once

#define ARDUINO_LOW = 0;
#define ARDUINO_HIGH = 255;

enum class ArduinoBytecodeType
{
    Handshake = 0,
    Acknowledge = 1,
    UpdateInputData = 2,
    UpdateOutputData = 3
};

enum class ArduinoComponentType
{
    LED = 0,
    Button = 1,
    Switch = 2
};
