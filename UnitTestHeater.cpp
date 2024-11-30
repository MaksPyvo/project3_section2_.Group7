#include "UnitTestHeater.h"
void UnitTestHeater::testDefaultConstructor() {
    Heater heater;
    QCOMPARE(heater.getHeatFlow(), 0);
    QCOMPARE(heater.getMaxHeat(), 100);
    QCOMPARE(heater.getMinHeat(), 0);
}

void UnitTestHeater::testParameterizedConstructor() {
    Heater heater(50, 120, 10);
    QCOMPARE(heater.getHeatFlow(), 50);
    QCOMPARE(heater.getMaxHeat(), 120);
    QCOMPARE(heater.getMinHeat(), 10);
}

void UnitTestHeater::testSetHeatFlowWithinRange() {
    Heater heater;
    heater.setMinHeat(10);
    heater.setMaxHeat(90);
    heater.setHeatFlow(50);
    QCOMPARE(heater.getHeatFlow(), 50);  // Value within the range
}

void UnitTestHeater::testSetHeatFlowBelowMin() {
    Heater heater;
    heater.setMinHeat(10);
    heater.setMaxHeat(90);
    heater.setHeatFlow(5);  // Below the minimum
    QCOMPARE(heater.getHeatFlow(), 0);  // Heat flow should not change
}

void UnitTestHeater::testSetHeatFlowAboveMax() {
    Heater heater;
    heater.setMinHeat(10);
    heater.setMaxHeat(90);
    heater.setHeatFlow(95);  // Above the maximum
    QCOMPARE(heater.getHeatFlow(), 0);  // Heat flow should not change
}
void UnitTestHeater::testSetHeatFlowAtMin() {
    Heater heater;
    heater.setMinHeat(10);
    heater.setMaxHeat(90);
    heater.setHeatFlow(10);  // Exactly at the minimum
    QCOMPARE(heater.getHeatFlow(), 10);
}

void UnitTestHeater::testSetHeatFlowAtMax() {
    Heater heater;
    heater.setMinHeat(10);
    heater.setMaxHeat(90);
    heater.setHeatFlow(90);  // Exactly at the maximum
    QCOMPARE(heater.getHeatFlow(), 90);
}
void UnitTestHeater::testReadFromFile() {
    // Create a temporary test file with known values
    QString filePath = "Heater.txt";
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << "60\n10\n100\n";  // heatFlow, min, max
        file.close();
    }

    Heater heater;
    heater.ReadFromFile();
    QCOMPARE(heater.getHeatFlow(), 60);
    QCOMPARE(heater.getMinHeat(), 10);
    QCOMPARE(heater.getMaxHeat(), 100);

    // Clean up the temporary file
    file.remove();
}

void UnitTestHeater::testWriteToFile() {
    Heater heater(75, 150, 25);  // Initialize the heater with known values
    heater.WriteToFile();

    // Read from the output file and verify
    QFile file("Temperature.txt");
    QVERIFY(file.open(QIODevice::ReadOnly | QIODevice::Text));
    QTextStream in(&file);
    QCOMPARE(in.readLine().toInt(), 75);  // Heat Flow
    QCOMPARE(in.readLine().toInt(), 25);  // Min Heat
    QCOMPARE(in.readLine().toInt(), 150); // Max Heat
    file.close();

    // Clean up the output file
    file.remove();
}
void UnitTestHeater::testTurnOn() {
    Heater heater;
    heater.turnOn(); // Call the turnOn method (inherited from Device)
    QVERIFY(heater.getStatus()); // Check that the heater status is true
}

void UnitTestHeater::testTurnOff() {
    Heater heater;
    heater.turnOff(); // Call the turnOff method (inherited from Device)
    QVERIFY(!heater.getStatus()); // Check that the heater status is false
}

