#include "InstrumentsPanel.h"

#include <iomanip>
#include <iostream>
#include "../Arduino/ArduinoDefinitions.h"
#include "../Arduino/ArduinoCommunicationManager.h"
#include "../Arduino/Components/ArduinoComponent.h"



InstrumentsPanel::InstrumentsPanel()
{

}

InstrumentsPanel::~InstrumentsPanel()
{
    DestroyComponents();
}

void InstrumentsPanel::Load(std::string const& portName)
{
    m_arduino->Load(this);
    m_arduino->Connect(portName);
}

void InstrumentsPanel::Unload()
{
    m_arduino->Disconnect();
    DestroyComponents();
}

void InstrumentsPanel::Update()
{
    m_arduino->Update();
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
