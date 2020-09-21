#pragma once
#include "../Program.h"

class ArduinoTestProgram : public IProgram
{
public:
    virtual void Begin() override;
    virtual void End() override;
    virtual void Update() override;
    virtual bool IsRunning() const override { return m_running; }
    virtual int GetExitCode() const override { return 0; }

private:
    bool m_running = false;
};
