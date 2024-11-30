
#include "UnitTestLight.h"


void UnitTestLight::testDefaultConstructor() {
    Light light;
    QCOMPARE(light.getBrightness(), 0);
    QCOMPARE(light.getMinBrightness(), 0);
    QCOMPARE(light.getMaxBrightness(), 100);
}

void UnitTestLight::testSetGetBrightness() {
    Light light;
    light.setBrightness(50);
    QCOMPARE(light.getBrightness(), 50);
}

void UnitTestLight::testSetGetMinBrightness() {
    Light light;
    light.setMinBrightness(10);
    QCOMPARE(light.getMinBrightness(), 10);
}

void UnitTestLight::testSetGetMaxBrightness() {
    Light light;
    light.setMaxBrightness(90);
    QCOMPARE(light.getMaxBrightness(), 90);
}
void UnitTestLight::testSetBrightnessBelowMin() {
    Light light;
    light.setMinBrightness(0);
    light.setMaxBrightness(100);
    light.setBrightness(-10);  // Below the minimum
    QCOMPARE(light.getBrightness(), 0);  // Should default to minimum
}

void UnitTestLight::testSetBrightnessAboveMax() {
    Light light;
    light.setMinBrightness(0);
    light.setMaxBrightness(100);
    light.setBrightness(110);  // Above the maximum
    QCOMPARE(light.getBrightness(), 0);  // Should default to = 0;
}


void UnitTestLight::testReadFromFile() {
    // Create a temporary file with known values
    QString testFilePath = "test_light_input.txt";
    QFile file(testFilePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << "60\n10\n90\n"; // Sample values
        file.close();
    }

    // Test reading from the file
    Light light;
    light.readFromFile("test_light_input.txt");

    QCOMPARE(light.getMinBrightness(), 10);
    QCOMPARE(light.getMaxBrightness(), 90);
    QCOMPARE(light.getBrightness(), 60);

    // Clean up the temporary file
    file.remove();
}

void UnitTestLight::testWriteToFile() {
    Light light;
    light.setBrightness(75);
    light.setMinBrightness(15);
    light.setMaxBrightness(85);

    // Write to the file
    light.writeToFile("LightOut.txt");

    // Read the file back to check content
    QFile file("LightOut.txt");
    QVERIFY(file.open(QIODevice::ReadOnly | QIODevice::Text));
    QTextStream in(&file);

    QCOMPARE(in.readLine().toInt(), 75);
    QCOMPARE(in.readLine().toInt(), 15);
    QCOMPARE(in.readLine().toInt(), 85);

    file.close();

    // Clean up the output file
    file.remove();

}
void UnitTestLight::testTurnOn() {
    Light light;
    light.turnOn(); // Call the turnOn method (inherited from Device)
    QVERIFY(light.getStatus()); // Check that the light status is true
}

void UnitTestLight::testTurnOff() {
    Light light;
    light.turnOff(); // Call the turnOff method (inherited from Device)
    QVERIFY(!light.getStatus()); // Check that the light status is false
}

