#include "ArduinoCommunicationManager.h"

#include "ArduinoDefinitions.h"
#include "ArduinoSerial.h"
#include "Commands/ArduinoCommand.h"
#include "Commands/ArduinoCommandFactory.h"
#include "Components/ArduinoComponent.h"
#include "Components/ArduinoComponentFactory.h"
#include "../Core/InstrumentsPanel.h"



ArduinoCommunicationManager::~ArduinoCommunicationManager()
{
    ClearAllCommandQueues();
}

void ArduinoCommunicationManager::Load(InstrumentsPanel* owningPanel)
{

}

void ArduinoCommunicationManager::Unload()
{

}

void ArduinoCommunicationManager::Update()
{
    if (m_serial->IsConnected())
    {
        if (m_serial->HasErrors())
        {
            m_serial->Disconnect();
            return;
        }

        BYTE commandByte;
        BYTE bufferSize;
        if (m_serial->ReadBytes(&commandByte, 1) > 0 && m_serial->ReadBytes(&bufferSize, 1) > 0)
        {
            ArduinoCommandType const commandType = static_cast<ArduinoCommandType>(commandByte);
            if (commandType == ArduinoCommandType::Acknowledge)
            {
                m_canSendCommands = true;
            }
            else if (bufferSize > 0)
            {
                BYTE* buffer = new BYTE[bufferSize];
                m_serial->ReadBytes(buffer, bufferSize);
                ArduinoCommand* receivedCommand = ArduinoCommandFactory::BuildCommand(commandType, static_cast<size_t>(bufferSize), buffer);
                EnqueueCommand(m_receivedCommands, receivedCommand);
                delete[] buffer;
            }
        }

        //PrintDataToConsole();
    }
}

void ArduinoCommunicationManager::Connect(std::string const& serialPortName)
{
    m_serial->Connect(serialPortName);
}

void ArduinoCommunicationManager::Disconnect()
{
    m_serial->Disconnect();
}

void ArduinoCommunicationManager::ClearAllCommandQueues()
{
    ClearCommandQueue(m_receivedCommands);
    ClearCommandQueue(m_commandsToSend);
}

void ArduinoCommunicationManager::ClearCommandQueue(std::queue<ArduinoCommand*>& commandQueue) const
{
    while (commandQueue.size() > 0)
    {
        delete commandQueue.front();
        commandQueue.pop();
    }
}

void ArduinoCommunicationManager::EnqueueCommand(std::queue<ArduinoCommand*>& commandQueue, ArduinoCommand* command) const
{
    commandQueue.push(command);
}
ArduinoCommand* ArduinoCommunicationManager::DequeueCommand(std::queue<ArduinoCommand*>& commandQueue) const
{
    if (commandQueue.size() > 0)
    {
        ArduinoCommand* command = commandQueue.front();
        commandQueue.pop();
        return command;
    }
    else
    {
        return nullptr;
    }
}
