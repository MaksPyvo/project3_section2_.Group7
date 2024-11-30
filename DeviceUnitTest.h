#ifndef DEVICETEST_H
#define DEVICETEST_H

#include <QObject>
#include <QtTest/QtTest>
#include "Device.h"

class DeviceTest : public QObject {
    Q_OBJECT

private slots:
    void DefaultConstructor_NameStatusWorkingStatus();   // UT-DEV-001
    void ParameterizedConstructor_HeaterOnWorking();      // UT-DEV-002
    void TurnOn_StatusTrue();                              // UT-DEV-003
    void TurnOff_StatusFalse();                            // UT-DEV-004
    void SetWorkingStatusToWorking_WorkingStatusTrue();   // UT-DEV-005
    void SetWorkingStatusToIdle_WorkingStatusFalse();     // UT-DEV-006
    void SetNameOfDevice_Heater();                        // UT-DEV-007
    void GetStatus_ReturnsTrue_WhenTurnedOn();             // UT-DEV-008
    void GetStatus_ReturnsFalse_WhenTurnedOff();           // UT-DEV-009
    void GetWorkingStatus_ReturnsTrue_WhenWorking();       // UT-DEV-0010
    void GetWorkingStatus_ReturnsFalse_WhenIdle();         // UT-DEV-0011
    void GetName_ReturnsHeater();                          // UT-DEV-012
};

#endif // DEVICETEST_H
