#include "FlightInstrumentsProgram.h"

#include <iostream>
#include <string>
#include "InstrumentsPanel.h"



///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
FlightInstrumentsProgram::FlightInstrumentsProgram()
{
    std::cout << "===========================================" << std::endl;
    std::cout << "||  Flight Instruments Program  --  v.0.0.0" << std::endl;
    std::cout << "===========================================" << std::endl;


}

FlightInstrumentsProgram::~FlightInstrumentsProgram()
{


    std::cout << "===========================================" << std::endl;
    std::cout << "||  PROGRAM ENDED" << std::endl;
    std::cout << "===========================================" << std::endl;
}



///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
void FlightInstrumentsProgram::PreLoad()
{
    std::cout << std::endl << "Loading program..." << std::endl;
}

void FlightInstrumentsProgram::Load()
{
    m_instrumentsPanels.push_back(new InstrumentsPanel());
    m_instrumentsPanels[0]->Load("COM4");
}

void FlightInstrumentsProgram::PostLoad()
{
    std::cout << "...Program loaded!" << std::endl << std::endl;
    m_running = true;
}



///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
void FlightInstrumentsProgram::PreUnload()
{
    m_running = false;
    std::cout << "Unloading program..." << std::endl << std::endl;
}

void FlightInstrumentsProgram::Unload()
{
    for (InstrumentsPanel* panel : m_instrumentsPanels)
    {
        delete panel;
    }
    m_instrumentsPanels.clear();
}

void FlightInstrumentsProgram::PostUnload()
{
    std::cout << "...Program unloaded!" << std::endl << std::endl;
}



///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
void FlightInstrumentsProgram::Loop()
{
    for (InstrumentsPanel* panel : m_instrumentsPanels)
    {
        panel->Loop();
    }
}
