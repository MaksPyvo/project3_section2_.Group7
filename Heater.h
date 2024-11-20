#ifndef HEATER_H
#define HEATER_H
#include "Device.h"
#include <QFile>
#include <QTextStream>
#include <QString>
//Heater class inter face
class Heater:public Device{
private:
    int heatFlow;
    int maxHeatFlow;
    int minHeatFlow;
public:
    Heater();
    Heater(int currentHeat, int maximum, int minimum);
    void setHeatFlow(int heat);
    int getHeatFlow();
    void setMaxHeat(int max);
    int getMaxHeat();
    void setMinHeat(int min);
    int getMinHeat();
    void ReadFromFile();
};
#endif // HEATER_H
