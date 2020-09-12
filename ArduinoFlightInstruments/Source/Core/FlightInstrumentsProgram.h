#pragma once

#include <vector>

class InstrumentsPanel;

class FlightInstrumentsProgram
{
public:
    FlightInstrumentsProgram();
    ~FlightInstrumentsProgram();

    void PreLoad();
    void Load();
    void PostLoad();

    void PreUnload();
    void Unload();
    void PostUnload();

    void Loop();

    inline bool IsRunning() const { return m_running; }

private:
    std::vector<InstrumentsPanel*> m_instrumentsPanels;
    bool m_running = false;
};
