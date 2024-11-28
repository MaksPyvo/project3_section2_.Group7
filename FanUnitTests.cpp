#include "FanUnitTests.h"

FanUnitTests::FanUnitTests() {}

void FanUnitTests::testDefaultConstructor() {
    Fan fan;
    QCOMPARE(fan.getSpeedLevel(), 0);
    QCOMPARE(fan.getStatus(), false);
}

void FanUnitTests::testSetSpeedLevelValidInput() {
    Fan fan;
    fan.setSpeedLevel(3);
    QCOMPARE(fan.getSpeedLevel(), 3);
}

void FanUnitTests::testSetSpeedLevelInvalidInput() {
    Fan fan;
    fan.setSpeedLevel(-1); // Invalid input
    QCOMPARE(fan.getSpeedLevel(), 0); // Should remain at the default value

    fan.setSpeedLevel(6); // Invalid input
    QCOMPARE(fan.getSpeedLevel(), 0); // Should remain at the default value
}

void FanUnitTests::testGetSpeedLevel() {
    Fan fan;
    fan.setSpeedLevel(3);
    QCOMPARE(fan.getSpeedLevel(), 3);
}

void FanUnitTests::testTurnOn() {
    Fan fan;
    fan.turnOn();
    QCOMPARE(fan.getStatus(), true);
}

void FanUnitTests::testTurnOff() {
    Fan fan;
    fan.turnOn();
    fan.turnOff();
    QCOMPARE(fan.getStatus(), false);
}

void FanUnitTests::testReadFromFile() {
    Fan fan;
    fan.readDataFromFile(); // Assuming the file exists and has a valid value
    QCOMPARE(fan.getSpeedLevel(), 2); // Replace 2 with the expected value from the file
}

void FanUnitTests::testWriteToFile() {
    Fan fan;
    int speedLevel = 3;
    fan.setSpeedLevel(speedLevel);
    fan.writeDataToFile();
    fan.readDataFromFile();
    QCOMPARE(fan.getSpeedLevel(), speedLevel);
}