#include "WaterPump.h"
#include <iostream>
#include <chrono>
#include <thread>
//Group7-ROB.
//Constructor with initialization of attributes and sensor.
WaterPump::WaterPump(Sensor* sensor)
    : moistureSensor(sensor), currentMoisture(0.0f), desiredMoisture(70.0f), pumpRate(1.6f), pumpStatus("OFF") {
    setName("Water Pump");
}
//Set the desired moisture level within a valid range (60% to 80%).
void WaterPump::setDesiredMoisture(float desiredLevel) {
    //Condition.
    if (desiredLevel >= 60.0f && desiredLevel <= 80.0f) {
        desiredMoisture = desiredLevel;
    } else {
        std::cout << "Invalid moisture level. It should be between 60% and 80%." << std::endl;
    }
}
//Get the desired moisture level.
float WaterPump::getDesiredMoisture() const {
    return desiredMoisture;
}
//Check the current moisture from the sensor and update the pump status.
void WaterPump::checkSoilMoisture() {
    //Get moisture from the sensor (Sensor class function).
    currentMoisture = moistureSensor->currentMoistureLevel();
    std::cout << "Current moisture: " << currentMoisture << "%" << std::endl;
    //Update the pump status based on the moisture level.
    updatePumpStatus();
}
//Set the pump activation condition (checks every 2 seconds).
void WaterPump::pumpActivationCondition() {
    // This method will be called in a loop every 2 seconds to check if the pump should turn on/off.
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        checkSoilMoisture();
    }
}
//Update the pump status based on moisture level thresholds.
void WaterPump::updatePumpStatus() {
    //Condition.
    //Turn on the pump if moisture is below 60%, while pump is off.
    if (currentMoisture < 60.0f && pumpStatus == "OFF") {
        turnOn();
    }
    //Turn off the pump if moisture is above 80%, while pump is on.
    else if (currentMoisture > 80.0f && pumpStatus == "ON") {
        turnOff();
    }
}
//Turn the pump ON and update the pump status.
void WaterPump::turnOn() {
    pumpStatus = "ON";
    Device::turnOn();    //turnOn() method from Device class.
    std::cout << "Water pump is ON." << std::endl;
}

//Turn the pump OFF and update the pump status.
void WaterPump::turnOff() {
    pumpStatus = "OFF";
    Device::turnOff();   //turnOff() method from the Device class.
    std::cout << "Water pump is OFF." << std::endl;
}
// Getter for the current moisture level.
float WaterPump::getCurrentMoisture() const {
    return currentMoisture;
}
// Getter for the pump status ("ON" or "OFF").
std::string WaterPump::getPumpStatus() const {
    return pumpStatus;
}
// Getter for the pump rate (Liters per minute)
float WaterPump::getPumpRate() const {
    return pumpRate;  // Return the current pump rate
}
// Save pump data to a file.
void WaterPump::saveFile(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << desiredMoisture << "\n";
        outFile << pumpStatus << "\n";
        outFile.close();
        std::cout << "Pump data saved to " << filename << std::endl;
    } else {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
    }
}
// Load pump data from a file.
void WaterPump::readFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (inFile.is_open()) {
        inFile >> desiredMoisture;
        inFile >> pumpStatus;
        inFile.close();
        std::cout << "Pump data loaded from " << filename << std::endl;
    } else {
        std::cerr << "Error: Unable to open file for reading." << std::endl;
    }
}
