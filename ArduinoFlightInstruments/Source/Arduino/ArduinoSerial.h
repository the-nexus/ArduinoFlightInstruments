// Based on implementation from
// https://playground.arduino.cc/Interfacing/CPPWindows/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <windows.h>

#define ARDUINO_RESET_DELAY 2000

class ArduinoSerial
{
public:
    ~ArduinoSerial();

    // To open and close a connection
    bool Connect(std::string const& portName);
    void Disconnect();

    // To read and write data on the arduino serial comm
    int ReadData(char* buffer, DWORD const maxCharsToRead);
    bool WriteData(char const* buffer, DWORD const charsToWrite);

    // Getters
    inline bool IsConnected() { return m_connected; }

private:
    HANDLE m_serialHandle;
    COMSTAT m_status;
    DWORD m_errors;

    bool m_connected = false;
};
