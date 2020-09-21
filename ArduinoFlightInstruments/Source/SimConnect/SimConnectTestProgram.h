#pragma once
#include "../Program.h"

#include <windows.h>
#include "SimConnect.h"

class SimConnectTestProgram : public IProgram
{
public:
    virtual void Begin() override;
    virtual void End() override;
    virtual void Update() override;
    virtual bool IsRunning() const override { return m_running; }
    virtual int GetExitCode() const override { return 0; }

    void SetRunning(bool const isRunning) { m_running = isRunning; }
    void SetThrottlePercent(double const throttle) { m_throttlePercent = throttle; }
    double GetThrottlePercent() const { return m_throttlePercent; }
    HANDLE const& GetSimConnectHandle() const { return m_simConnectHandle; }

    static void CALLBACK OnSimConnectEvent(SIMCONNECT_RECV* pData, DWORD cbData, void* pContext);

private:
    double m_throttlePercent = 0.f;
    bool m_running = false;
    HANDLE  m_simConnectHandle = nullptr;
};
