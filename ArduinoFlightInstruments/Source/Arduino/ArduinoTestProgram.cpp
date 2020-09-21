#include "ArduinoTestProgram.h"

#include <iostream>



void ArduinoTestProgram::Begin()
{
    m_serial.Connect("COM4");
    if (!m_serial.IsConnected())
    {
        return;
    }

    m_commands.clear();
    m_commands.push_back("");
    m_running = true;
}

void ArduinoTestProgram::End()
{
    m_serial.Disconnect();
    m_running = false;
}

void ArduinoTestProgram::Update()
{
    if (!m_serial.IsConnected())
    {
        m_running = false;
        return;
    }

    // Process received data to assemble commands
    char receivedCharBuffer[64];
    size_t const bufferSize = static_cast<size_t>(m_serial.ReadBytes(&receivedCharBuffer, 64));
    for (size_t idx = 0; idx < bufferSize; ++idx)
    {
        char const receivedChar = receivedCharBuffer[idx];
        if (receivedChar == '\n')
        {
            m_commands.back();
            m_commands.push_back("");
        }
        else
        {
            m_commands.back() += receivedChar;
        }
    }

    if (m_commands.size() > 1)
    {
        std::cout << "-----" << std::endl;
    }

    while (m_commands.size() > 1)
    {
        std::string const& cmdToProcess = m_commands.front();
        size_t const cmdSpcIdx = cmdToProcess.find(' ', 0);
        bool const hasFoundSpc = cmdSpcIdx < cmdToProcess.size();

        std::cout << "[RCV] STR = " << cmdToProcess << std::endl;

        std::string const cmd = hasFoundSpc ? cmdToProcess.substr(0, cmdSpcIdx) : cmdToProcess;
        std::string const args = hasFoundSpc ? cmdToProcess.substr(cmdSpcIdx + 1) : "";

        if (cmd.compare("l_led") == 0)
        {
            if (args.compare("on") == 0)
            {
                char cmdToSend[10] = "r_led on\n";
                m_serial.WriteBytes(&cmdToSend, 10);
                std::cout << "[SND] STR = " << cmdToSend << std::endl;
            }
            else if (args.compare("off") == 0)
            {
                char cmdToSend[11] = "r_led off\n";
                m_serial.WriteBytes(&cmdToSend, 11);
                std::cout << "[SND] STR = " << cmdToSend << std::endl;
            }
        }

        m_commands.erase(m_commands.begin());
    }
}
