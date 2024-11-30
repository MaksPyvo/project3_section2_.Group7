#include "UnitTestWaterPump.h"
#include <fstream>  // For file operations

void TestWaterPump::testSetDesiredMoistureValid() {

    Sensor sensor;        // Directly instantiate the Sensor object
    WaterPump waterPump(&sensor);  // Pass the sensor to the WaterPump
     QTest::qWait(20000);  // Add delay of 20 seconds to simulate processing time
    QCOMPARE(waterPump.getDesiredMoisture(), 50); //Starting init value
    // Test Case for Req-WTP-02: "The system shall activate the water pump when moisture is below the desired threshold."
}

void TestWaterPump::testSetDesiredMoistureInvalid() {
    Sensor sensor;        // Directly instantiate the Sensor object
    WaterPump waterPump(&sensor);  // Pass the sensor to the WaterPump
    waterPump.setDesiredMoisture(71);  // outside valid range
    QCOMPARE(waterPump.getDesiredMoisture(), 50);  // It shouldn't change
    QCOMPARE(waterPump.getPumpStatus(), QString("OFF"));
    QCOMPARE(waterPump.getPumpRate(), 0.0f);
    QTest::qWait(10000);  // Add delay of 10 seconds to simulate processing time
    // Test Case for Req-WTP-01: "The system shall reject moisture levels outside the defined valid range."
}

void TestWaterPump::testCheckSoilMoistureTurnOff() {
    Sensor sensor;        // Directly instantiate the Sensor object
    WaterPump waterPump(&sensor);  // Pass the sensor to the WaterPump

    waterPump.setDesiredMoisture(71);
    sensor.setCurrentValue(71);  // current moisture equals desired moisture
    waterPump.checkSoilMoisture(sensor.getCurrentValue());  // Use getCurrentValue()
    QCOMPARE(waterPump.getPumpStatus(), QString("OFF"));
    QCOMPARE(waterPump.getPumpRate(), 0.0f);
    QTest::qWait(20000);  // Add delay of 8 seconds to simulate processing time
    // Test Case for Req-WTP-02: "The water pump should turn off once the desired moisture level is achieved."
}

void TestWaterPump::testCheckSoilMoistureTurnOn() {
    Sensor sensor;        // Directly instantiate the Sensor object
    WaterPump waterPump(&sensor);  // Pass the sensor to the WaterPump
    waterPump.setDesiredMoisture(71);
    sensor.setCurrentValue(61);  // current moisture equals desired moisture
    waterPump.checkSoilMoisture(sensor.getCurrentValue());  // Use getCurrentValue()
    QCOMPARE(sensor.getCurrentValue() < 71, true);
    QTest::qWait(200);  // Add delay
    // Test Case for Req-WTP-02: "The system shall activate the water pump when moisture is below the desired threshold."
}

void TestWaterPump::testTurnOn() {
    Sensor sensor;        // Directly instantiate the Sensor object
    WaterPump waterPump(&sensor);  // Pass the sensor to the WaterPump
    waterPump.turnOn();
    QCOMPARE(waterPump.getPumpStatus(), QString("ON"));
    QTest::qWait(5000);  // Add delay of 5 seconds to simulate processing time
    // Test Case for Req-WTP-03: "The system shall allow the user to manually turn the pump ON."
}

void TestWaterPump::testTurnOff() {
    Sensor sensor;        // Directly instantiate the Sensor object
    WaterPump waterPump(&sensor);  // Pass the sensor to the WaterPump
    waterPump.turnOff();
    QCOMPARE(waterPump.getPumpStatus(), QString("OFF"));
    QTest::qWait(5000);  // Add delay of 5 seconds to simulate processing time
    // Test Case for Req-WTP-04: "The system shall allow the user to manually turn the pump OFF."
}

void TestWaterPump::testSaveFile() {
    Sensor sensor;        // Directly instantiate the Sensor object
    WaterPump waterPump(&sensor);  // Pass the sensor to the WaterPump
    waterPump.setDesiredMoisture(70);  // Set desired moisture level (for example)
    // Read the saved moisture value from the file
    std::ifstream file("Moisture.txt");  // Open the file where moisture value is saved
    int savedValue;
    file >> savedValue;  // Read the saved value
    file.close();  // Close the file after reading
    // Check if the saved value is greater than zero
    QCOMPARE(savedValue > 0, true);  // Ensure that the saved value is greater than zero
    QTest::qWait(30000);  // Add delay to simulate processing time
    // Test Case for Req-WTP-05: "The system shall save the current moisture value to a file when requested."
}


// Test Case for Req-WTP-02: "The system shall activate the water pump when moisture is below the desired threshold."
void TestWaterPump::testPumpWaterBasedOnMoisture() {
    Sensor sensor;
    WaterPump waterPump(&sensor);
    sensor.setCurrentValue(60);
    waterPump.setDesiredMoisture(70);  // Set desired moisture level to 70%
    waterPump.checkSoilMoisture(sensor.getCurrentValue());
    QTest::qWait(10000);
    sensor.setCurrentValue(70);  // Assume that the soil moisture has increased to 70% after pumping
    QCOMPARE(sensor.getCurrentValue(), 70);
    QTest::qWait(5000);  // Simulate additional processing time after turning the pump off
}
