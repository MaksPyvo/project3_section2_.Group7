#ifndef UNITTESTIRRIGATIONSYSTEM_H
#define UNITTESTIRRIGATIONSYSTEM_H

#include <QtTest/QtTest>
#include "IrrigationSystem.h"
#include "WaterPump.h" // Include WaterPump to set up the irrigation system for testing

// Test class for Irrigation system using QTest framework
class TestIrrigationSystem : public QObject {
    Q_OBJECT

private slots:
    void testActivateIrrigation();  // Verifies irrigation system activation when the water pump is ON (REQ-IRR-02).
    void testDeactivateIrrigation();  // Verifies irrigation system deactivation when the water pump is OFF (REQ-IRR-03).
    void testIrrigationWhenPumpIsOn();  // Tests irrigation loop behavior when the pump is ON (REQ-IRR-04).
    void testIrrigationWhenPumpIsOff();  // Tests irrigation loop behavior when the pump is OFF (REQ-IRR-04).
    void testStopIrrigation();  // Verifies that the irrigation loop stops correctly (REQ-IRR-04).
    void testDisplayFlowRate();  // Verifies correct display of pump flow rate (REQ-IRR-06).

private:
    WaterPump* waterPump;  // Pointer to WaterPump for testing
    Irrigation* irrigationSystem;  // Pointer to Irrigation system
};

#endif // UNITTESTIRRIGATIONSYSTEM_H
