#ifndef LIGHT_H
#define LIGHT_H
#include "Device.h"

class Light:public Device{
private:
    int brightness, min, max;

public:
    Light();
    void setBrightness(int);
    int getBrightness();
    void setMinBrightness(int);
    int getMinBrightness();
    void setMaxBrightness(int);
    int getMaxBrightness();

};
#endif // LIGHT_H
