#include "IrrigationSystem.h"
#include <iostream>
#include <thread>

Irrigation::Irrigation(WaterPump* waterPump)
    : waterPump(waterPump) {}

void Irrigation::activateIrrigation() {
    if (waterPump->isPumpOn()) {
        std::cout << "Irrigation system is ACTIVE. Flow rate: 1.6 L/min." << std::endl;
    }
}

void Irrigation::deactivateIrrigation() {
    if (!waterPump->isPumpOn()) {
        std::cout << "Irrigation system is INACTIVE." << std::endl;
    }
}
//Check pump status every 2 seconds.
void Irrigation::irrigationLoop() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(2));

        if (waterPump->isPumpOn()) {
            activateIrrigation();
        } else {
            deactivateIrrigation();
        }
    }
}

void Irrigation::displayFlowRate() {
    std::cout << "Flow rate of pump: 1.6 L/min." << std::endl;
}
