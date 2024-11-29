#include "ExhaustUnitTests.h"
#include "Exhaust.h"

ExhaustUnitTests::ExhaustUnitTests() {}

void ExhaustUnitTests::testDefaultConstructor() {
    Exhaust exhaust;
    QCOMPARE(exhaust.checkIfExhaustOpened(), false);
    QCOMPARE(exhaust.getStatus(), false);
}

void ExhaustUnitTests::testOpenExhaust() {
    Exhaust exhaust;
    exhaust.openExhaust();
    QCOMPARE(exhaust.checkIfExhaustOpened(), true);
}

void ExhaustUnitTests::testCloseExhaust() {
    Exhaust exhaust;
    exhaust.openExhaust();
    exhaust.closeExhaust();
    QCOMPARE(exhaust.checkIfExhaustOpened(), false);
}

void ExhaustUnitTests::testCheckIfExhaustOpened() {
    Exhaust exhaust;
    QCOMPARE(exhaust.checkIfExhaustOpened(), false); // Initially closed

    exhaust.openExhaust();
    QCOMPARE(exhaust.checkIfExhaustOpened(), true);
}

void ExhaustUnitTests::testTurnOn() {
    Exhaust exhaust;
    exhaust.turnOn();
    QCOMPARE(exhaust.getStatus(), true);
}

void ExhaustUnitTests::testTurnOff() {
    Exhaust exhaust;
    exhaust.turnOn();
    exhaust.turnOff();
    QCOMPARE(exhaust.getStatus(), false);
}

void ExhaustUnitTests::testReadFromFile() {
    Exhaust exhaust;
    exhaust.closeExhaust();
    exhaust.writeDataToFile();
    exhaust.readDataFromFile();
    QCOMPARE(exhaust.checkIfExhaustOpened(), false);
}

void ExhaustUnitTests::testWriteToFile() {
    Exhaust exhaust;
    exhaust.openExhaust();
    exhaust.writeDataToFile();
    exhaust.readDataFromFile(); // Assuming the file exists and has a valid value
    QCOMPARE(exhaust.checkIfExhaustOpened(), true); // Replace true with the expected value from the file
}
