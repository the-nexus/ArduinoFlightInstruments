#include "ArduinoCommandFactory.h"

#include "ArduinoCommand.h"
#include "ArduinoCommandHandshake.h"
#include "../ArduinoDefinitions.h"

ArduinoCommand* ArduinoCommandFactory::BuildCommand(ArduinoCommandType const commandType, size_t const bufferSize, BYTE const* buffer)
{
    switch (commandType)
    {
    case ArduinoCommandType::Handshake:
        return BuildCommand<ArduinoCommandHandshake>(bufferSize, buffer);

    default:
        return nullptr;
    }
}

template <class CommandType>
CommandType* ArduinoCommandFactory::BuildCommand(size_t const bufferSize, BYTE const* buffer)
{
    CommandType* command = new CommandType();
    command->SetFromBytes(bufferSize, buffer);
    return command;
}

