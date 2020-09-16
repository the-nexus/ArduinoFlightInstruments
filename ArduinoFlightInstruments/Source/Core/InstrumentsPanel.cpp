#include "InstrumentsPanel.h"

#include <iomanip>
#include <iostream>
#include "../Arduino/ArduinoDefinitions.h"
#include "../Arduino/ArduinoCommunicator.h"
#include "../Arduino/ArduinoSerial.h"
#include "../Arduino/Components/ArduinoComponent.h"



InstrumentsPanel::InstrumentsPanel()
{
    m_serial = new ArduinoSerial();
}

InstrumentsPanel::~InstrumentsPanel()
{
    DestroyComponents();
    delete m_serial;
}

void InstrumentsPanel::Load(std::string const& portName)
{
    m_serial->Connect(portName);
}

void InstrumentsPanel::Unload()
{
    m_serial->Disconnect();
    DestroyComponents();
}

void InstrumentsPanel::Loop()
{
    if (m_serial->IsConnected())
    {
        if (m_serial->HasErrors())
        {
            m_serial->Disconnect();
            return;
        }

        BYTE bytecodeVal;
        if (m_serial->ReadBytes(&bytecodeVal, 1) > 0)
        {
            ArduinoBytecodeType const bytecode = static_cast<ArduinoBytecodeType>(bytecodeVal);
            switch (bytecode)
            {
            case ArduinoBytecodeType::Handshake:
                DestroyComponents();
                ArduinoCommunicator::HandleSerial_Handshake(m_serial, m_inputComponents, m_inputComponentCount, m_outputComponents, m_outputComponentCount);
                break;

            default:
                break;
            }
        }

        PrintDataToConsole();
    }

}

void InstrumentsPanel::DestroyComponents()
{
    if (m_inputComponents != nullptr)
    {
        for (size_t componentIndex = 0; componentIndex < m_inputComponentCount; ++componentIndex)
        {
            if (m_inputComponents[componentIndex] != nullptr)
            {
                delete m_inputComponents[componentIndex];
                m_inputComponents[componentIndex] = nullptr;
            }
        }
        delete m_inputComponents;
        m_inputComponents = nullptr;
    }

    if (m_outputComponents != nullptr)
    {
        for (size_t componentIndex = 0; componentIndex < m_outputComponentCount; ++componentIndex)
        {
            if (m_outputComponents[componentIndex] != nullptr)
            {
                delete m_outputComponents[componentIndex];
                m_outputComponents[componentIndex] = nullptr;
            }
        }
        delete m_outputComponents;
        m_outputComponents = nullptr;
    }
}

void InstrumentsPanel::PrintDataToConsole() const
{
    if (m_inputComponentCount > 0 || m_outputComponentCount > 0)
    {
        std::cout << std::setw(3);

        std::cout << "Input :  ";
        if (m_inputComponents != nullptr)
        {
            for (size_t componentIndex = 0; componentIndex < m_inputComponentCount; ++componentIndex)
            {
                ArduinoComponent const* component = m_inputComponents[componentIndex];
                unsigned int const byteValue = component ? static_cast<unsigned int>(component->GetByteValue()) : 0;
                std::cout << byteValue << "  ";
            }
        }

        std::cout << "\t  Output :  ";
        if (m_outputComponents != nullptr)
        {
            for (size_t componentIndex = 0; componentIndex < m_outputComponentCount; ++componentIndex)
            {
                ArduinoComponent const* component = m_outputComponents[componentIndex];
                unsigned int const byteValue = component ? static_cast<unsigned int>(component->GetByteValue()) : 0;
                std::cout << byteValue << "  ";
            }
        }

        std::cout << std::endl;
    }
}
