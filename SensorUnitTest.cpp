#include "SensorUnitTest.h"
#include <QFile>
#include <QTextStream>
#include <QString>

void SensorTest::DefaultConstructor_UndefinedValues() {
    Sensor sensor;
    QCOMPARE(sensor.getName(), QString("Undefined Sensor"));
    QCOMPARE(sensor.getUnitOfMeasurement(), QString("undefined unit of measurement"));
    QCOMPARE(sensor.getCurrentValue(), -1);
}

void SensorTest::ParameterizedConstructor_InitializedValues() {
    char file_name[]="Temperature.txt";
    Sensor sensor("Temperature Sensor", "Celsius", file_name, 25);
    QCOMPARE(sensor.getName(), QString("Temperature Sensor"));
    QCOMPARE(sensor.getUnitOfMeasurement(), QString("Celsius"));
    QCOMPARE(sensor.getCurrentValue(), 25);
}

void SensorTest::SetName_TemperatureSensor() {
    Sensor sensor;
    sensor.setName("Temperature Sensor");
    QCOMPARE(sensor.getName(), QString("Temperature Sensor"));
}

void SensorTest::SetUnitOfMeasurement_Celsius() {
    Sensor sensor;
    sensor.setUnitOfMeasurement("Celsius");
    QCOMPARE(sensor.getUnitOfMeasurement(), QString("Celsius"));
}

void SensorTest::ReadDataFromFile_Update_CurrentValue_25() {
    // Assume the file "Temperature.txt" contains the value "25"
    QFile file("Temperature.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << "25\n";
    file.close();

    Sensor sensor;
    char file_name[]="Temperature.txt";
    sensor.setReadingFileName(file_name);
    sensor.readDataFromFile();
    QCOMPARE(sensor.getCurrentValue(), 25);
}

void SensorTest::ReadDataFromFile_ErrorOpeningFile_Minus100() {
    // Using a non-existent file
    Sensor sensor;
    char file_name[]="Invalid.txt";
    sensor.setReadingFileName(file_name);
    sensor.readDataFromFile();
    QCOMPARE(sensor.getCurrentValue(), -100);  // Error should set value to -100
}

void SensorTest::ReadDataFromFile_ErrorReadingValue_Minus100() {
    // Simulate reading an invalid value
    QFile file("Temperature.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << "$\n";  // Invalid value
    file.close();

    Sensor sensor;
    char file_name[]="Temperature.txt";
    sensor.setReadingFileName(file_name);
    sensor.readDataFromFile();
    QCOMPARE(sensor.getCurrentValue(), -100);  // Error in reading value should set to -100
}

void SensorTest::SetCurrentValue_25() {
    Sensor sensor;
    sensor.setCurrentValue(25);
    QCOMPARE(sensor.getCurrentValue(), 25);
}

void SensorTest::GetCurrentValue_25() {
    Sensor sensor;
    sensor.setCurrentValue(25);
    QCOMPARE(sensor.getCurrentValue(), 25);
}

void SensorTest::GetName_TemperatureSensor() {
    char file_name[]="Temperature.txt";
    Sensor sensor("Temperature Sensor", "Celsius", file_name, 25);
    QCOMPARE(sensor.getName(), QString("Temperature Sensor"));
}

void SensorTest::GetUnitOfMeasurement_Celsius() {
    char file_name[]="Temperature.txt";
    Sensor sensor("Temperature Sensor", "Celsius", file_name, 25);
    QCOMPARE(sensor.getUnitOfMeasurement(), QString("Celsius"));
}
