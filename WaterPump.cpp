#include "WaterPump.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>

// Group7
WaterPump::WaterPump(Sensor* sensor)
    : moistureSensor(sensor), currentMoisture(0.0f), desiredMoisture(50.0f), pumpRate(0.0f), pumpStatus("OFF") {
    setNameOfDevice("Water Pump");  // Using setNameOfDevice method from Device class
}

void WaterPump::setDesiredMoisture(float desiredLevel) {
    if (getPumpStatus() == "ON"){
    if (desiredLevel >= 60.0f && desiredLevel <= 80.0f) {
        desiredMoisture = desiredLevel;
        turnOn();
        pumpRate = 1.6;
    }
        else {
        std::cout << "Invalid desired level. It should be between 60% and 80%." << std::endl;
        turnOff();
        pumpRate = 0;
    }
    }
}

float WaterPump::getDesiredMoisture() const {
    return desiredMoisture;
}

void WaterPump::checkSoilMoisture(float moistureValue) {
       currentMoisture = moistureValue;
    std::cout << "Current moisture: " << currentMoisture << "%" << std::endl;
        if (currentMoisture >= desiredMoisture) {
            turnOff();
            pumpRate = 0;
            std::cout << "Desired moisture level reached. Pump is turned OFF." << std::endl;
            // Save the current state to file
            saveFile("PumpStop.txt");
            currentMoisture = desiredMoisture; //continue here.
        }

    updatePumpStatus();
}


void WaterPump::pumpActivationCondition() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        checkSoilMoisture(currentMoisture);
    }
}

void WaterPump::updatePumpStatus() {
    if (getPumpStatus() == "ON"){
    if (currentMoisture < 60.0f && pumpStatus == "OFF") {
        turnOn();
         pumpRate = 1.6;
    } else if (currentMoisture > 80.0f && pumpStatus == "ON") {
        turnOff();
         pumpRate = 0;
    }
    }
}

void WaterPump::turnOn() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    pumpStatus = "ON";
    Device::turnOn();
    std::cout << "Water pump is ON." << std::endl;
}

void WaterPump::turnOff() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
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
        outFile << currentMoisture << "\n";
        outFile.close();
        std::cout << "Pump data saved to " << filename << std::endl;
    } else {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
    }
}

void WaterPump::readFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (inFile.is_open())
    {
        int value;
        inFile >> value; if (value == -100)
        {
            std::cerr << "Error reading moisture data." << std::endl; currentMoisture = -1;
        }
        else { currentMoisture = value; } inFile.close();
    } else { std::cerr << "Unable to open moisture data file." << std::endl;
    }
}


