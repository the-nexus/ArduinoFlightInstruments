#pragma once

class IProgram
{
public:
    virtual void Begin() = 0;
    virtual void End() = 0;
    virtual void Update() = 0;
    virtual bool IsRunning() const = 0;
    virtual int GetExitCode() const = 0;
};
