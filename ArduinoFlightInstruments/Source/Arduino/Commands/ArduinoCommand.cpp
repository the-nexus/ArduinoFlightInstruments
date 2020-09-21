#include "ArduinoCommand.h"

ArduinoCommand::~ArduinoCommand()
{
    if (m_buffer)
    {
        delete[] m_buffer;
    }
}

void ArduinoCommand::SetFromBytes(size_t const bufferSize, BYTE const* buffer)
{
    if (m_buffer)
    {
        delete[] m_buffer;
    }

    m_buffer = new BYTE[2 + bufferSize];
    m_buffer[0] = static_cast<BYTE>(m_commandType);
    m_buffer[1] = static_cast<BYTE>(bufferSize);
    memcpy(&m_buffer[2], buffer, bufferSize);
    m_bufferSize = bufferSize;
    DissectBuffer();
}

BYTE const* ArduinoCommand::GetAsBytes(size_t& outBufferSize) const
{
    outBufferSize = m_bufferSize;
    return m_buffer;
}
