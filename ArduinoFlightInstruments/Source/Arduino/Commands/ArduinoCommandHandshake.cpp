#include "ArduinoCommandHandshake.h"

void ArduinoCommandHandshake::DissectBuffer()
{

}

void ArduinoCommandHandshake::AssembleBuffer()
{

}

//void ArduinoCommunicationManager::HandleSerial_Handshake(ArduinoSerial* serial, ArduinoComponent**& outInputComponents, size_t& outInputComponentCount, ArduinoComponent**& outOutputComponents, size_t& outOutputComponentsCount)
//{
//    BYTE inputComponentCountByte = 0;
//    if (serial->ReadBytes(&inputComponentCountByte, 1) > 0 && inputComponentCountByte > 0)
//    {
//        outInputComponentCount = static_cast<size_t>(inputComponentCountByte);
//        outInputComponents = new ArduinoComponent * [outInputComponentCount];
//
//        for (size_t componentIndex = 0; componentIndex < outInputComponentCount; ++componentIndex)
//        {
//            BYTE componentTypeByte = 0;
//            if (serial->ReadBytes(&componentTypeByte, 1) > 0)
//            {
//                ArduinoComponentType const componentType = static_cast<ArduinoComponentType>(componentTypeByte);
//                outInputComponents[componentIndex] = ArduinoComponentFactory::BuildComponent(componentType);
//            }
//            else
//            {
//                outInputComponents[componentIndex] = nullptr;
//            }
//        }
//    }
//
//    BYTE outputComponentCount = 0;
//    if (serial->ReadBytes(&outputComponentCount, 1) > 0 && outputComponentCount > 0)
//    {
//        outOutputComponentsCount = static_cast<size_t>(outputComponentCount);
//        outOutputComponents = new ArduinoComponent * [outputComponentCount];
//
//        for (size_t componentIndex = 0; componentIndex < outOutputComponentsCount; ++componentIndex)
//        {
//            BYTE componentTypeByte = 0;
//            if (serial->ReadBytes(&componentTypeByte, 1) > 0)
//            {
//                ArduinoComponentType const componentType = static_cast<ArduinoComponentType>(componentTypeByte);
//                outOutputComponents[componentIndex] = ArduinoComponentFactory::BuildComponent(componentType);
//            }
//            else
//            {
//                outOutputComponents[componentIndex] = nullptr;
//            }
//        }
//    }
//
//    BYTE byteToWrite = static_cast<BYTE>(ArduinoCommandType::Handshake);
//    serial->WriteBytes(&byteToWrite, 1);
//}
