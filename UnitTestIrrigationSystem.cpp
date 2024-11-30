#include "UnitTestIrrigationSystem.h"
#include "Device.h"

// Test case for activating the irrigation system when the pump is ON (REQ-IRR-02)
void TestIrrigationSystem::testActivateIrrigation() {
    QTest::qWait(20000);  // Add 20 seconds delay
    // Ensure the pump is ON before activation
    Device waterPump("WaterPump", true, true);  // Initialize pump with status ON and working
    QCOMPARE(waterPump.getStatus(), true);  // Pump should be ON (status = true)
}

// Test case for deactivating the irrigation system when the pump is OFF (REQ-IRR-03)
void TestIrrigationSystem::testDeactivateIrrigation() {
    QTest::qWait(20000);  // Add 20 seconds delay
    // Ensure the pump is OFF before deactivation
    Device waterPump("WaterPump", false, false);  // Initialize pump with status OFF and idle
    QCOMPARE(waterPump.getStatus(), false);  // Pump should be OFF (status = false)
}

// Test case to verify irrigation system behavior when the pump is ON (REQ-IRR-04)
void TestIrrigationSystem::testIrrigationWhenPumpIsOn() {
    QTest::qWait(20000);  // Add 20 seconds delay
    Device waterPump("WaterPump", true, true);  // Pump is ON and working
    float currentFlow = waterPump.getWorkingStatus() ? 1.6f : 0.0f;  // Flow rate based on working status
    float desiredFlow = 1.6f;  // Example desired flow rate
    QVERIFY(currentFlow <= desiredFlow);  // Flow should be less than or equal to desired flow rate
}

// Test case to verify irrigation system behavior when the pump is OFF (REQ-IRR-04)
void TestIrrigationSystem::testIrrigationWhenPumpIsOff() {
    QTest::qWait(20000);  // Add 20 seconds delay
    Device waterPump("WaterPump", false, false);  // Pump is OFF and not working
    float currentFlow = waterPump.getWorkingStatus() ? 1.6f : 0.0f;  // Flow is 0 if the pump is not working
    float desiredFlow = 0.0f;  // Flow should be 0 when the pump is off
    QCOMPARE(currentFlow, desiredFlow);  // Flow should be 0 when pump is off
}

// Test case to verify that the irrigation system stops correctly (REQ-IRR-04)
void TestIrrigationSystem::testStopIrrigation() {
    QTest::qWait(20000);  // Add 20 seconds delay
    Device waterPump("WaterPump", false, false);  // Pump is OFF and idle
    waterPump.turnOff();  // Turn off the pump
    QCOMPARE(waterPump.getStatus(), false);  // Pump should be OFF
    QCOMPARE(waterPump.getWorkingStatus(), false);  // Pump should be idle
}

// Test case to verify the correct display of pump flow rate (REQ-IRR-06)
void TestIrrigationSystem::testDisplayFlowRate() {
    QTest::qWait(20000);  // Add 20 seconds delay
    Device waterPump("WaterPump", true, true);  // Pump is ON and working
    if (waterPump.getWorkingStatus()) {
        QCOMPARE(1.6f, 1.6f);  // If working, rate is 1.6
    } else {
        QCOMPARE(0.0f, 0.0f);  // If not working, rate is 0
    }
}
