#pragma once

#include "../ArduinoDefinitions.h"
#include <windows.h>

class ArduinoCommand
{
public:
    ArduinoCommand() = default;
    virtual ~ArduinoCommand();

    void SetFromBytes(size_t const bufferSize, BYTE const* buffer);
    BYTE const* GetAsBytes(size_t& outBufferSize) const;

    virtual void DissectBuffer() = 0;
    virtual void AssembleBuffer() = 0;

protected:
    ArduinoCommand(ArduinoCommandType const commandType) : m_commandType(commandType) {}

    ArduinoCommandType m_commandType = ArduinoCommandType::Invalid;
    bool m_needsBufferUpdate = true;
    BYTE* m_buffer = nullptr;
    size_t m_bufferSize = 0;
};
