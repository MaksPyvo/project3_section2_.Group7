#ifndef FAN_H
#define FAN_H

#include "Device.h"

class Fan : public Device {
private:
    int speedLevel;

public:
    Fan();
    void setSpeedLevel(int speed);
    int getSpeedLevel();
    void readDataFromFile();
    void writeDataToFile();
};

#endif
