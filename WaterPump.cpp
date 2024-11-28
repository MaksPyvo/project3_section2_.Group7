#include "WaterPump.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>

// Group7-ROB

WaterPump::WaterPump(Sensor* sensor)
    : moistureSensor(sensor), currentMoisture(0.0f), desiredMoisture(70.0f), pumpRate(1.6f), pumpStatus("OFF") {
    setNameOfDevice("Water Pump");  // Using setNameOfDevice method from Device class
}

void WaterPump::setDesiredMoisture(float desiredLevel) {
    if (desiredLevel >= 60.0f && desiredLevel <= 80.0f) {
        desiredMoisture = desiredLevel;
    } else {
        std::cout << "Invalid moisture level. It should be between 60% and 80%." << std::endl;
    }
}

float WaterPump::getDesiredMoisture() const {
    return desiredMoisture;
}

void WaterPump::checkSoilMoisture() {
    currentMoisture = moistureSensor->getCurrentValue();
    std::cout << "Current moisture: " << currentMoisture << "%" << std::endl;
    updatePumpStatus();
}

void WaterPump::pumpActivationCondition() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        checkSoilMoisture();
    }
}

void WaterPump::updatePumpStatus() {
    if (currentMoisture < 60.0f && pumpStatus == "OFF") {
        turnOn();
    } else if (currentMoisture > 80.0f && pumpStatus == "ON") {
        turnOff();
    }
}

void WaterPump::turnOn() {
    pumpStatus = "ON";
    Device::turnOn();
    std::cout << "Water pump is ON." << std::endl;
}

void WaterPump::turnOff() {
    pumpStatus = "OFF";
    Device::turnOff();
    std::cout << "Water pump is OFF." << std::endl;
}

float WaterPump::getCurrentMoisture() const {
    return currentMoisture;
}

std::string WaterPump::getPumpStatus() const {
    return pumpStatus;
}

float WaterPump::getPumpRate() const {
    return pumpRate;
}

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
