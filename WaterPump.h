#ifndef WATERPUMP_H
#define WATERPUMP_H

#include <string>
#include "Sensor.h"
#include "Device.h"

// Group7-ROB
class WaterPump : public Device {
public:
    WaterPump(Sensor* sensor);
    void setDesiredMoisture(float desiredLevel);
    float getDesiredMoisture() const;
    void checkSoilMoisture(float);
    void turnOn();
    void turnOff();
    void updatePumpStatus();
    void pumpActivationCondition();
    float getCurrentMoisture() const;
    std::string getPumpStatus() const;
    float getPumpRate() const;
    void saveFile(const std::string& filename = "PumpStop.txt") const;
    void saveFileTwo(const std::string& filename = "Moisture.txt") const;
    void readFile(const std::string& filename = "Moisture.txt");

private:
    float currentMoisture;
    float desiredMoisture;
    std::string pumpStatus;
    float pumpRate;
    Sensor* moistureSensor;
};

#endif // WATERPUMP_H
