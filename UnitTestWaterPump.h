#ifndef UNITTESTWATERPUMP_H
#define UNITTESTWATERPUMP_H

#include <QtTest/QtTest>
#include "WaterPump.h"
#include "Sensor.h"  // Include the real Sensor class

// Test class using QTest
class TestWaterPump : public QObject {
    Q_OBJECT

private slots:
    void testSetDesiredMoistureValid();      // REQ-WTP-02: Verify setting desired moisture within valid range (60-80%)
    void testSetDesiredMoistureInvalid();    // REQ-WTP-03: Ensure invalid moisture setting (outside range 60-80%) is rejected
    void testCheckSoilMoistureTurnOff();     // REQ-WTP-04: Check if pump turns off when soil moisture reaches desired level
    void testPumpWaterBasedOnMoisture();     // REQ-WTP-01: Pump water based on soil moisture level to reach the desired value
    void testCheckSoilMoistureTurnOn();      // REQ-WTP-04: Check if pump turns on when moisture is below desired level
    void testTurnOn();                       // REQ-WTP-06: Test turning the pump on manually
    void testTurnOff();                      // REQ-WTP-06: Test turning the pump off manually
    void testSaveFile();                     // REQ-WTP-07: Save the desired moisture value to a file for later use

private:
    Sensor* sensor;   // Using the real Sensor class now
    WaterPump* waterPump;
};

#endif // UNITTESTWATERPUMP_H
