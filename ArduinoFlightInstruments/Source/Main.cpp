// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.

// INFO TO MAKE THIS PROGRAM WORK:
// https://playground.arduino.cc/Interfacing/CPPWindows/
// https://docs.microsoft.com/en-us/previous-versions/microsoft-esp/cc526983(v=msdn.10)?redirectedfrom=MSDN
// https://todbot.com/blog/2006/12/06/arduino-serial-c-code-to-talk-to-arduino/

#include "Core/FlightInstrumentsProgram.h"

int main()
{
    FlightInstrumentsProgram program;
    program.Load();
    program.PostLoad();
    while (program.IsRunning())
    {
        program.Loop();
    }
    program.PreUnload();
    program.Unload();
}
