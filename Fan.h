#ifndef FAN_H
#define FAN_H

#include "Device.h"

class Fan : public Device {
private:
    int speedLevel;
    int previousSpeedLevel = 0;

public:
    Fan();
    int getSpeedLevel();
    void setSpeedLevel(int speed);
    void changeTemperature();
    void readDataFromFile();
    void writeDataToFile();
};

#endif
