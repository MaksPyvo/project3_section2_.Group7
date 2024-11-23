#ifndef EXHAUST_H
#define EXHAUST_H

#include "Device.h"

class Exhaust : public Device {
private:
    bool isOpened;

public:
    Exhaust();
    void openExhaust();
    void closeExhaust();
    void changeHumidityLevel();
    bool checkIfExhaustOpened();
    void readDataFromFile();
    void writeDataToFile();
};

#endif
