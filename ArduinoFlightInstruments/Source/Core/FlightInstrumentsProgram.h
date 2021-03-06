#pragma once
#include <vector>
#include "../Program.h"

class InstrumentsPanel;

class FlightInstrumentsProgram : public IProgram
{
public:
    virtual void Begin() override;
    virtual void End() override;
    virtual void Update() override;
    virtual bool IsRunning() const override { return m_running; }
    virtual int GetExitCode() const override{ return 0; }

private:
    std::vector<InstrumentsPanel*> m_instrumentsPanels;
    bool m_running = false;
};
