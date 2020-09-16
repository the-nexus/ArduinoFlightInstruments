// Based on implementation from
// https://playground.arduino.cc/Interfacing/CPPWindows/

#pragma once

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
    int ReadBytes(void* byteBuffer, DWORD const maxBytesToRead) const;
    bool WriteBytes(void const* byteBuffer, DWORD const bytesToWrite);

    // Getters
    inline bool IsConnected() const { return m_connected; }
    inline bool HasErrors() const { return m_errors > 0; }

private:
    HANDLE m_serialHandle;
    mutable COMSTAT m_status;
    mutable DWORD m_errors;

    bool m_connected = false;
};
