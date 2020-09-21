// INFO TO MAKE THIS PROJECT WORK:
// https://playground.arduino.cc/Interfacing/CPPWindows/
// https://docs.microsoft.com/en-us/previous-versions/microsoft-esp/cc526983(v=msdn.10)?redirectedfrom=MSDN
// https://todbot.com/blog/2006/12/06/arduino-serial-c-code-to-talk-to-arduino/
// https://github.com/dcs-bios/dcs-bios-arduino-library



// Add available programs to this list
#include "Arduino/ArduinoTestProgram.h"
#include "Core/FlightInstrumentsProgram.h"
#include "SimConnect/SimConnectTestProgram.h"



// EDIT HERE! This line selects the program class that will be executed
#define PROGRAM_CLASS ArduinoTestProgram



int main()
{
    IProgram* program = new PROGRAM_CLASS();

    program->Begin();
    while (program->IsRunning())
    {
        program->Update();
    }
    program->End();

    int const exitCode = program->GetExitCode();
    delete program;
    return exitCode;
}
