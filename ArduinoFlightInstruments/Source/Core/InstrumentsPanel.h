#pragma once

#include <string>

class ArduinoCommunicationManager;
class ArduinoComponent;
class ArduinoSerial;

class InstrumentsPanel
{
public:
    InstrumentsPanel();
    ~InstrumentsPanel();

    void Load(std::string const& portName);
    void Unload();
    void Update();

    void DestroyComponents();

private:
    void PrintDataToConsole() const;

    size_t m_inputComponentCount = 0;
    size_t m_outputComponentCount = 0;
    ArduinoComponent** m_inputComponents = nullptr;
    ArduinoComponent** m_outputComponents = nullptr;
    ArduinoCommunicationManager* m_arduino;
};
