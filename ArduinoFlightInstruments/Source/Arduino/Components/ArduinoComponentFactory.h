#pragma once

enum class ArduinoComponentType;
class ArduinoComponent;

class ArduinoComponentFactory
{
public:
    static ArduinoComponent* BuildComponent(ArduinoComponentType const componentType);
};
