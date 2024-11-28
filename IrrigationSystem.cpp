#include "IrrigationSystem.h"
#include <iostream>
#include <chrono>
#include <thread>

// Group 17 Irrigation implementation

// Constructor initializing the water pump and running flag
Irrigation::Irrigation(WaterPump* waterPump)
    : waterPump(waterPump), running(true) {}

// Activate the irrigation system if the water pump is on
void Irrigation::activateIrrigation() {
    if (waterPump->getPumpStatus() == "ON") {
        std::cout << "Irrigation system is ACTIVE. Flow rate: " << waterPump->getPumpRate() << " L/min." << std::endl;
    }
}

// Deactivate the irrigation system if the water pump is off
void Irrigation::deactivateIrrigation() {
    if (waterPump->getPumpStatus() == "OFF") {
        std::cout << "Irrigation system is INACTIVE." << std::endl;
    }
}

// Check pump status every 2 seconds and activate/deactivate irrigation accordingly
void Irrigation::irrigationLoop() {
    while (running) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        if (waterPump->getPumpStatus() == "ON") {
            activateIrrigation();
        } else {
            deactivateIrrigation();
        }
    }
}

// Stop the irrigation loop
void Irrigation::stopIrrigation() {
    running = false;
}

// Display the flow rate of the pump
void Irrigation::displayFlowRate() {
    std::cout << "Flow rate of pump: " << waterPump->getPumpRate() << " L/min." << std::endl;
}
