#ifndef IRRIGATION_H
#define IRRIGATION_H

#include "WaterPump.h"
#include <thread>
#include <atomic>

// Group 17 Irrigation header
class Irrigation {
public:
    // Constructor with a pointer to the WaterPump
    Irrigation(WaterPump* waterPump);

    // Methods
    void activateIrrigation();      // Activate irrigation system if pump is on
    void deactivateIrrigation();    // Deactivate irrigation system if pump is off
    void irrigationLoop();          // Loop to check pump status and activate irrigation
    void stopIrrigation();          // Stop the irrigation loop
    void displayFlowRate();         // Display the flow rate of the pump

private:
    WaterPump* waterPump;           // Pointer to the WaterPump
    std::atomic<bool> running;      // Atomic flag to control the irrigation loop
};

#endif // IRRIGATION_H
