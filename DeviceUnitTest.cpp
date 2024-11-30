#include "DeviceUnitTest.h"

void DeviceTest::DefaultConstructor_NameStatusWorkingStatus() {
    Device device;
    QCOMPARE(device.getName(), QString("undefined Device"));
    QCOMPARE(device.getStatus(), false);
    QCOMPARE(device.getWorkingStatus(), false);
}

void DeviceTest::ParameterizedConstructor_HeaterOnWorking() {
    Device device("Heater", true, true);
    QCOMPARE(device.getName(), QString("Heater"));
    QCOMPARE(device.getStatus(), true);
    QCOMPARE(device.getWorkingStatus(), true);
}

void DeviceTest::TurnOn_StatusTrue() {
    Device device;
    device.turnOn();
    QVERIFY(device.getStatus() == true);  // Check that the status is true after turnOn()
}

void DeviceTest::TurnOff_StatusFalse() {
    Device device;
    device.turnOff();
    QVERIFY(device.getStatus() == false);  // Check that the status is false after turnOff()
}

void DeviceTest::SetWorkingStatusToWorking_WorkingStatusTrue() {
    Device device;
    device.setWorkingStatusWorking();
    QVERIFY(device.getWorkingStatus() == true);  // Check that the working status is true (working)
}

void DeviceTest::SetWorkingStatusToIdle_WorkingStatusFalse() {
    Device device;
    device.setWorkingStatusIdle();
    QVERIFY(device.getWorkingStatus() == false);  // Check that the working status is false (idle)
}

void DeviceTest::SetNameOfDevice_Heater() {
    Device device;
    device.setNameOfDevice("Heater");
    QCOMPARE(device.getName(), QString("Heater"));  // Check that the name is set to "Heater"
}

void DeviceTest::GetStatus_ReturnsTrue_WhenTurnedOn() {
    Device device;
    device.turnOn();
    QCOMPARE(device.getStatus(), true);  // Check that the status is true when the device is turned on
}

void DeviceTest::GetStatus_ReturnsFalse_WhenTurnedOff() {
    Device device;
    device.turnOff();
    QCOMPARE(device.getStatus(), false);  // Check that the status is false when the device is turned off
}

void DeviceTest::GetWorkingStatus_ReturnsTrue_WhenWorking() {
    Device device;
    device.setWorkingStatusWorking();
    QCOMPARE(device.getWorkingStatus(), true);  // Check that the working status is true when it's set to working
}

void DeviceTest::GetWorkingStatus_ReturnsFalse_WhenIdle() {
    Device device;
    device.setWorkingStatusIdle();
    QCOMPARE(device.getWorkingStatus(), false);  // Check that the working status is false when it's set to idle
}

void DeviceTest::GetName_ReturnsHeater() {
    Device device("Heater", true, true);
    QCOMPARE(device.getName(), QString("Heater"));  // Check that the name is correctly returned
}
