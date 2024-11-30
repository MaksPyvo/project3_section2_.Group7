#ifndef UNITTESTLIGHT_H
#define UNITTESTLIGHT_H
#include <QObject>
#include <QtTest/QtTest>
#include "Light.h"

class UnitTestLight : public QObject {
    Q_OBJECT

private slots:
    void testDefaultConstructor();
    void testSetGetBrightness();
    void testSetGetMinBrightness();
    void testSetGetMaxBrightness();
    void testReadFromFile();
    void testWriteToFile();
    void testTurnOn();
    void testTurnOff();
    void testSetBrightnessBelowMin();
    void testSetBrightnessAboveMax();
};
#endif // UNITTESTLIGHT_H
