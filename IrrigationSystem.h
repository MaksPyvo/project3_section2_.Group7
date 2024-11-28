#ifndef IRRIGATION_H
#define IRRIGATION_H
//Water Pump Class.
#include "WaterPump.h"
//Group 17 Irrigation header.
class Irrigation {
public:
    Irrigation(WaterPump* waterPump);  // Constructor with a pointer to the WaterPump
    //Methods.
    void activateIrrigation();  // Activate irrigation system if pump is on
    void deactivateIrrigation();  // Deactivate irrigation system if pump is off
    void irrigationLoop();  // Loop to check pump status and activate irrigation
    void displayFlowRate();  // Display the flow rate of the pump

private:
    WaterPump* waterPump;  // Pointer to the WaterPump.
};

#endif // IRRIGATION_H

