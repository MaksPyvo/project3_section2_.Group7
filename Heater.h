#ifndef HEATER_H
#define HEATER_H
#include "Device.h"
//Heater class inter face
class Heater:public Device{
private:
    float heatFlow;
    float maxHeatFlow;
    float minHeatFlow;
public:
    Heater();
    Heater(float currentHeat, float maximum, float minimum);
    void setHeatFlow(float heat);
    float getHeatFlow();
    void setMaxHeat(float max);
    float getMaxHeat();
    void setMinHeat(float min);
    float getMinHeat();

};
#endif // HEATER_H
