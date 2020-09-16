#pragma once

#include <string>

class ArduinoComponent;
class ArduinoSerial;

class InstrumentsPanel
{
public:
    InstrumentsPanel();
    ~InstrumentsPanel();

    void Load(std::string const& portName);
    void Unload();
    void Loop();

    void DestroyComponents();

private:
    void PrintDataToConsole() const;

    ArduinoSerial* m_serial;
    std::string m_portName = "";

    size_t m_inputComponentCount = 0;
    size_t m_outputComponentCount = 0;
    ArduinoComponent** m_inputComponents = nullptr;
    ArduinoComponent** m_outputComponents = nullptr;
};
