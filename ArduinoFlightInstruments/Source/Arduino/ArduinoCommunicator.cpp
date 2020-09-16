#include "ArduinoCommunicator.h"

#include "ArduinoDefinitions.h"
#include "ArduinoSerial.h"
#include "Components/ArduinoComponent.h"
#include "Components/ArduinoComponentFactory.h"



void ArduinoCommunicator::HandleSerial_Handshake(ArduinoSerial* serial, ArduinoComponent**& outInputComponents, size_t& outInputComponentCount, ArduinoComponent**& outOutputComponents, size_t& outOutputComponentsCount)
{
    BYTE inputComponentCountByte = 0;
    if (serial->ReadBytes(&inputComponentCountByte, 1) > 0 && inputComponentCountByte > 0)
    {
        outInputComponentCount = static_cast<size_t>(inputComponentCountByte);
        outInputComponents = new ArduinoComponent*[outInputComponentCount];

        for (size_t componentIndex = 0; componentIndex < outInputComponentCount; ++componentIndex)
        {
            BYTE componentTypeByte = 0;
            if (serial->ReadBytes(&componentTypeByte, 1) > 0)
            {
                ArduinoComponentType const componentType = static_cast<ArduinoComponentType>(componentTypeByte);
                outInputComponents[componentIndex] = ArduinoComponentFactory::BuildComponent(componentType);
            }
            else
            {
                outInputComponents[componentIndex] = nullptr;
            }
        }
    }

    BYTE outputComponentCount = 0;
    if (serial->ReadBytes(&outputComponentCount, 1) > 0 && outputComponentCount > 0)
    {
        outOutputComponentsCount = static_cast<size_t>(outputComponentCount);
        outOutputComponents = new ArduinoComponent*[outputComponentCount];

        for (size_t componentIndex = 0; componentIndex < outOutputComponentsCount; ++componentIndex)
        {
            BYTE componentTypeByte = 0;
            if (serial->ReadBytes(&componentTypeByte, 1) > 0)
            {
                ArduinoComponentType const componentType = static_cast<ArduinoComponentType>(componentTypeByte);
                outOutputComponents[componentIndex] = ArduinoComponentFactory::BuildComponent(componentType);
            }
            else
            {
                outOutputComponents[componentIndex] = nullptr;
            }
        }
    }

    BYTE byteToWrite = static_cast<BYTE>(ArduinoBytecodeType::Handshake);
    serial->WriteBytes(&byteToWrite, 1);
}

void ArduinoCommunicator::HandleSerial_Acknowledge(ArduinoSerial* serial)
{

}

void ArduinoCommunicator::HandleSerial_ReceiveInputData(ArduinoSerial* serial, BYTE const* inputBuffer, const DWORD bufferSize)
{

}

void ArduinoCommunicator::HandleSerial_SendOutputData(ArduinoSerial* serial, BYTE const* outputBuffer, DWORD& bufferSize)
{

}
