#ifndef HEATER_H
#define HEATER_H
#include "Device.h"
#include <QFile>
#include <QTextStream>
#include <QString>
//Heater class inter face
class Heater:public Device{
private:
    double heatFlow;
    double maxHeatFlow;
    double minHeatFlow;
public:
    Heater();
    Heater(double currentHeat, double maximum, double minimum);
    void setHeatFlow(double heat);
    double getHeatFlow();
    void setMaxHeat(double max);
    double getMaxHeat();
    void setMinHeat(double min);
    double getMinHeat();
    void ReadFromFile();
};
#endif // HEATER_H
