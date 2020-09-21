#pragma once

#include <windows.h>

class ArduinoCommand;
enum class ArduinoCommandType;

class ArduinoCommandFactory
{
public:
    static ArduinoCommand* BuildCommand(ArduinoCommandType const commandType, size_t const bufferSize, BYTE const* buffer);

    template <class T>
    static T* BuildCommand(size_t const bufferSize, BYTE const* buffer);
};
