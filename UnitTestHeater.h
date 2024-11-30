#ifndef UNITTESTHEATER_H
#define UNITTESTHEATER_H

#include <QObject>
#include <QtTest/QtTest>
#include "Heater.h"

class UnitTestHeater : public QObject {
    Q_OBJECT

private slots:
    void testDefaultConstructor();        // UTC-HTR-001
    void testParameterizedConstructor();  // UTC-HTR-002
    void testSetHeatFlowWithinRange();    // UTC-HTR-003
    void testSetHeatFlowBelowMin();       // UTC-HTR-004
    void testSetHeatFlowAboveMax();       // UTC-HTR-005
    void testReadFromFile();              // UTC-HTR-006
    void testWriteToFile();
    void testTurnOn();
    void testTurnOff();        // Custom addition for completeness
    void testSetHeatFlowAtMax();
    void testSetHeatFlowAtMin();
};

#endif // UNITTESTHEATER_H
