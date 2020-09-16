#pragma once

#include <windows.h>

class ArduinoComponent
{
public:
    inline BYTE GetByteValue() const { return m_byteValue; }
    inline void SetByteValue(BYTE const newByteValue) { m_byteValue = newByteValue; }

    inline bool IsAssigned() const { return m_assigned; }
    inline void SetAssigned(bool const isAssigned) { m_assigned = isAssigned; }

private:
    BYTE m_byteValue = 0;
    bool m_assigned = false;
};
