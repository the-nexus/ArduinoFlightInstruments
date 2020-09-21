#include "SimConnectTestProgram.h"

#include <iostream>

enum GROUP_ID {
    GROUP_KEYS,
};
enum INPUT_ID {
    INPUT_KEYS,
};

enum EVENT_ID {
    EVENT_SIM_START,
    EVENT_A,
    EVENT_D
};

enum DATA_DEFINE_ID {
    DEFINITION_THROTTLE,
};

enum DATA_REQUEST_ID {
    REQUEST_THROTTLE,
};



void SimConnectTestProgram::Begin()
{
    HRESULT hr;
    if (SUCCEEDED(SimConnect_Open(&m_simConnectHandle, "SimConnect Test Program", nullptr, 0, 0, 0)))
    {
        std::cout << "Connected to MSFS2020!" << std::endl << std::endl;

        // Set up a data definition for the throttle control
        hr = SimConnect_AddToDataDefinition(m_simConnectHandle, DEFINITION_THROTTLE,
            "GENERAL ENG THROTTLE LEVER POSITION:1", "percent");

        // Request a simulation started event
        hr = SimConnect_SubscribeToSystemEvent(m_simConnectHandle, EVENT_SIM_START, "SimStart");

        // Create two private key events to control the throttle
        hr = SimConnect_MapClientEventToSimEvent(m_simConnectHandle, EVENT_A);
        hr = SimConnect_MapClientEventToSimEvent(m_simConnectHandle, EVENT_D);

        // Link the events to some keyboard keys
        hr = SimConnect_MapInputEventToClientEvent(m_simConnectHandle, INPUT_KEYS, "a", EVENT_A);
        hr = SimConnect_MapInputEventToClientEvent(m_simConnectHandle, INPUT_KEYS, "d", EVENT_D);

        // Ensure the input events are off until the sim is up and running
        hr = SimConnect_SetInputGroupState(m_simConnectHandle, INPUT_KEYS, SIMCONNECT_STATE_OFF);

        // Sign up for notifications
        hr = SimConnect_AddClientEventToNotificationGroup(m_simConnectHandle, GROUP_KEYS, EVENT_A);
        hr = SimConnect_AddClientEventToNotificationGroup(m_simConnectHandle, GROUP_KEYS, EVENT_D);

        std::cout << "Please launch a flight..." << std::endl;

        m_running = true;
    }
}

void SimConnectTestProgram::End()
{
    std::cout << std::endl << "Disconnected to MSFS2020. Goodbye!" << std::endl;
    m_running = false;
}

void SimConnectTestProgram::Update()
{
    SimConnect_CallDispatch(m_simConnectHandle, OnSimConnectEvent, this);
}

void CALLBACK SimConnectTestProgram::OnSimConnectEvent(SIMCONNECT_RECV* pData, DWORD cbData, void* pContext)
{
    SimConnectTestProgram* program = reinterpret_cast<SimConnectTestProgram*>(pContext);
    
    HRESULT hr;
    switch (pData->dwID)
    {
    case SIMCONNECT_RECV_ID_SIMOBJECT_DATA:
        {
            SIMCONNECT_RECV_SIMOBJECT_DATA* pObjData = (SIMCONNECT_RECV_SIMOBJECT_DATA*)pData;

            switch (pObjData->dwRequestID)
            {
            case REQUEST_THROTTLE:
                {
                    // Read and set the initial throttle control value
                    double const dataThrottlePercent = *reinterpret_cast<double*>(&pObjData->dwData);
                    program->SetThrottlePercent(dataThrottlePercent);
                    std::cout << "Received SC Event:    Updated Throttle = " << dataThrottlePercent << std::endl;

                    // Now turn the input events on
                    hr = SimConnect_SetInputGroupState(program->GetSimConnectHandle(), INPUT_KEYS, SIMCONNECT_STATE_ON);
                }

            default:
                break;
            }
            break;
        }

    case SIMCONNECT_RECV_ID_EVENT:
        {
            SIMCONNECT_RECV_EVENT* evt = (SIMCONNECT_RECV_EVENT*)pData;

            switch (evt->uEventID)
            {

            case EVENT_SIM_START:
            {
                // Send this request to get the user aircraft id
                hr = SimConnect_RequestDataOnSimObject(program->GetSimConnectHandle(), REQUEST_THROTTLE, DEFINITION_THROTTLE, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_ONCE);
                hr = SimConnect_RequestDataOnSimObject(program->GetSimConnectHandle(), REQUEST_THROTTLE, DEFINITION_THROTTLE, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_ONCE);
                std::cout << "Received SC Event:    Simulation Started" << std::endl;
            }
            break;

            case EVENT_A:
            {
                double currentThrottlePercent = program->GetThrottlePercent();
                // Increase the throttle
                if (currentThrottlePercent <= 95.0)
                {
                    currentThrottlePercent += 5.0;
                    program->SetThrottlePercent(currentThrottlePercent);
                    hr = SimConnect_SetDataOnSimObject(program->GetSimConnectHandle(), DEFINITION_THROTTLE, SIMCONNECT_OBJECT_ID_USER, 0, 0, sizeof(double), &currentThrottlePercent);
                    std::cout << "Received SC Event:    Increased Throttle (" << currentThrottlePercent << ")" << std::endl;
                }
            }
            break;

            case EVENT_D:
            {
                // Decrease the throttle
                double currentThrottlePercent = program->GetThrottlePercent();
                // Increase the throttle
                if (currentThrottlePercent >= 5.0)
                {
                    currentThrottlePercent -= 5.0;
                    program->SetThrottlePercent(currentThrottlePercent);
                    hr = SimConnect_SetDataOnSimObject(program->GetSimConnectHandle(), DEFINITION_THROTTLE, SIMCONNECT_OBJECT_ID_USER, 0, 0, sizeof(double), &currentThrottlePercent);
                    std::cout << "Received SC Event:    Decreased Throttle (" << currentThrottlePercent << ")" <<  std::endl;
                }
            }
            break;

            default:
                break;
            }
            break;
        }

    case SIMCONNECT_RECV_ID_QUIT:
        program->SetRunning(false);
        std::cout << "Received SC Event:    Quit" << pData->dwID << std::endl;
        break;

    default:
        std::cout << "Received Unhandled SC Event:    ID# " << pData->dwID << std::endl;
        break;
    }
}
