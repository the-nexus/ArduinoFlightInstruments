#pragma once

#include "ArduinoCommand.h"

class ArduinoCommandHandshake : public ArduinoCommand
{
public:
    ArduinoCommandHandshake() : ArduinoCommand(ArduinoCommandType::Handshake) {}

    virtual void DissectBuffer() override;
    virtual void AssembleBuffer() override;
};
