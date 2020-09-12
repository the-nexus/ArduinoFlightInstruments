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
    for (InstrumentsPanel* instrumentsPanel : m_instrumentsPanels)
    {
        delete instrumentsPanel;
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
    std::string command;
    std::cin >> command;

    std::cout << "Command: " << command << std::endl;

    if (command.compare("exit"))
    {
        m_running = false;
    }
}
