#include "ArduinoComponentFactory.h"

#include "ArduinoComponent.h"



ArduinoComponent* ArduinoComponentFactory::BuildComponent(ArduinoComponentType const componentType)
{
    //switch (componentType)
    {
    //default:
        return new ArduinoComponent();
    }
}
