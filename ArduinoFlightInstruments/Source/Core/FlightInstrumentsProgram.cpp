#include "FlightInstrumentsProgram.h"

#include "InstrumentsPanel.h"



void FlightInstrumentsProgram::Begin()
{
    m_instrumentsPanels.push_back(new InstrumentsPanel());
    m_instrumentsPanels[0]->Load("COM4");
    m_running = true;
}

void FlightInstrumentsProgram::End()
{
    for (InstrumentsPanel* panel : m_instrumentsPanels)
    {
        delete panel;
    }
    m_instrumentsPanels.clear();
}

void FlightInstrumentsProgram::Update()
{
    for (InstrumentsPanel* panel : m_instrumentsPanels)
    {
        panel->Update();
    }
}
