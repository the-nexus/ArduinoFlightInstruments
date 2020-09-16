// Based on implementation from
// https://playground.arduino.cc/Interfacing/CPPWindows/

#pragma once

#include <windows.h>

class ArduinoComponent;
class ArduinoSerial;

class ArduinoCommunicator
{
public:
    static void HandleSerial_Handshake(ArduinoSerial* serial, ArduinoComponent**& outInputComponents, size_t& outInputComponentCount, ArduinoComponent**& outOutputComponents, size_t& outOutputComponentsCount);
    static void HandleSerial_Acknowledge(ArduinoSerial* serial);
    static void HandleSerial_ReceiveInputData(ArduinoSerial* serial, BYTE const* inputBuffer, const DWORD bufferSize);
    static void HandleSerial_SendOutputData(ArduinoSerial* serial, BYTE const* outputBuffer, DWORD& bufferSize);
};
