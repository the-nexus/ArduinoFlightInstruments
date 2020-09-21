// Based on implementation from
// https://playground.arduino.cc/Interfacing/CPPWindows/

#pragma once

#include <windows.h>
#include <queue>

class ArduinoCommand;
class ArduinoComponent;
class ArduinoSerial;
class InstrumentsPanel;

class ArduinoCommunicationManager
{
public:
    ~ArduinoCommunicationManager();

    void Load(InstrumentsPanel* owningPanel);
    void Unload();
    void Update();

    void Connect(std::string const& serialPortName);
    void Disconnect();

    inline ArduinoCommand* ReceiveCommand() { return DequeueCommand(m_receivedCommands); }
    inline void SendCommand(ArduinoCommand* command) { EnqueueCommand(m_commandsToSend, command); }
    void ClearAllCommandQueues();

private:
    void EnqueueCommand(std::queue<ArduinoCommand*>& commandQueue, ArduinoCommand* command) const;
    ArduinoCommand* DequeueCommand(std::queue<ArduinoCommand*>& commandQueue) const;
    void ClearCommandQueue(std::queue<ArduinoCommand*>& commandQueue) const;

    std::queue<ArduinoCommand*> m_receivedCommands; // Received commands
    std::queue<ArduinoCommand*> m_commandsToSend; // Commands to send

    ArduinoSerial* m_serial = nullptr;
    bool m_hasReceivedHandshake = false;
    bool m_canSendCommands = false;
};
