#ifndef WATERPUMP_H
#define WATERPUMP_H
#include <string>
#include "Sensor.h"
#include "Device.h"
//Group7-ROB.
class WaterPump : public Device {
public:
    //Constructor that takes a pointer to the Sensor class.
    //WaterPump(Sensor* sensor);
    //Set the desired moisture level within a valid range.
    void setDesiredMoisture(float desiredLevel);
    //Get the desired moisture level.
    float getDesiredMoisture() const;
    //Check the current moisture from the sensor and update the pump status.
    void checkSoilMoisture();
    //Turn on the pump.
    void turnOn();
    //Turn off the pump.
    void turnOff();
    //Update the pump status based on current moisture level.
    void updatePumpStatus();
    //Set the pump activation condition (checks every 2 seconds).
    void pumpActivationCondition();
    //Getter for the current moisture level.
    float getCurrentMoisture() const;
    //Getter for the pump status ("ON" or "OFF").
    std::string getPumpStatus() const;
    //Getter for the pump rate (Liters per minute).
    float getPumpRate() const;
    //save, read FILE/IO.
    void saveFile(const std::string& filename) const;
    void loadFile(const std::string& filename);
private:
    float currentMoisture;  //Current soil moisture level.
    float desiredMoisture;  //User setting target moisture level.
    std::string pumpStatus; //Current pump status ("ON" or "OFF").
    float pumpRate;         //Pumping rate in Liters per minute.
    Sensor* moistureSensor; //Pointer to the SoilMoistureSensor.
};

#endif // WATERPUMP_H
