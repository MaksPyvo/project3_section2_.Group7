#ifndef SENSORTEST_H
#define SENSORTEST_H

#include <QObject>
#include <QtTest/QtTest>
#include "Sensor.h"

class SensorTest : public QObject {
    Q_OBJECT

private slots:
    void DefaultConstructor_UndefinedValues();    // UT-SEN-001
    void ParameterizedConstructor_InitializedValues(); // UT-SEN-002
    void SetName_TemperatureSensor();                      // UT-SEN-003
    void SetUnitOfMeasurement_Celsius();                     // UT-SEN-004
    void ReadDataFromFile_Update_CurrentValue_25();        // UT-SEN-006
    void ReadDataFromFile_ErrorOpeningFile_Minus100(); // UT-SEN-007
    void ReadDataFromFile_ErrorReadingValue_Minus100(); // UT-SEN-008
    void SetCurrentValue_25();     // UT-SEN-009
    void GetCurrentValue_25();              // UT-SEN-010
    void GetName_TemperatureSensor();                              // UT-SEN-011
    void GetUnitOfMeasurement_Celsius();                 // UT-SEN-012
};

#endif // SENSORTEST_H
