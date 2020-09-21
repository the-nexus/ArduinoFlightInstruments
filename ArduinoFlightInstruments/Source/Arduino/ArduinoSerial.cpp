// Based on implementation from
// https://playground.arduino.cc/Interfacing/CPPWindows/

#include "ArduinoSerial.h"

#include "../Tools/MathTools.h"
#include "../Tools/StringTools.h"



///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
ArduinoSerial::~ArduinoSerial()
{
    Disconnect();
}



///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
bool ArduinoSerial::Connect(std::string const& portName)
{
    if (IsConnected())
    {
        printf("ERROR! Already connected, can't attempt a new connection.\n");
        return false;
    }

    size_t const portNameLength = portName.length();
    if (portNameLength == 0)
    {
        printf("ERROR! Could not connect, port name is empty.\n");
        return false;
    }

    // Disconnect first to clean up data
    Disconnect();

    // Connect to the serial comm
    std::wstring const wPortName = StringTools::ToWString(portName);
    m_serialHandle = CreateFile(wPortName.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    // Handle the connection results and apply the comm parameters
    if (m_serialHandle == INVALID_HANDLE_VALUE)
    {
        DWORD const lastErrorCode = GetLastError();
        if (lastErrorCode == ERROR_FILE_NOT_FOUND)
        {
            printf("ERROR! Could not create handle, port name '%s' not found.\n", portName.c_str());
            return false;
        }
        else
        {
            printf("ERROR! Could not create handle, unknown reason.\n");
            return false;
        }
    }

    DCB dcbSerialParams;
    if (!GetCommState(m_serialHandle, &dcbSerialParams))
    {
        printf("ERROR! Could not get the current serial parameters.\n");
        return false;
    }

    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    dcbSerialParams.fDtrControl = DTR_CONTROL_ENABLE;

    if (!SetCommState(m_serialHandle, &dcbSerialParams))
    {
        printf("ERROR! Could not set the new serial parameters.\n");
        return false;
    }

    // Finalize the connection
    PurgeComm(m_serialHandle, PURGE_RXCLEAR | PURGE_TXCLEAR);
    m_connected = true;

    // Wait for the arduino board to reset
    Sleep(ARDUINO_RESET_DELAY);
    return true;
}

void ArduinoSerial::Disconnect()
{
    if (IsConnected())
    {
        CloseHandle(m_serialHandle);
        m_connected = false;
    }
}



///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
bool ArduinoSerial::HasBytes() const
{
    ClearCommError(m_serialHandle, &m_errors, &m_status);
    return m_status.cbInQue > 0;
}

int ArduinoSerial::ReadBytes(void* byteBuffer, DWORD const maxBytesToRead) const
{
    if (HasBytes())
    {
        DWORD const availableBytesToRead = m_status.cbInQue;
        DWORD const bytesToRead = MathTools::Min(availableBytesToRead, maxBytesToRead);

        DWORD bytesRead;
        if (ReadFile(m_serialHandle, byteBuffer, bytesToRead, &bytesRead, NULL))
        {
            return bytesRead;
        }
    }
    return 0;
}

bool ArduinoSerial::WriteBytes(void const* byteBuffer, DWORD const bytesToWrite)
{
    DWORD bytesWritten;
    if (WriteFile(m_serialHandle, byteBuffer, bytesToWrite, &bytesWritten, NULL))
    {
        return true;
    }

    ClearCommError(m_serialHandle, &m_errors, &m_status);
    return false;
}
