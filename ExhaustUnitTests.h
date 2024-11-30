#ifndef EXHAUSTUNITTESTs_H
#define EXHAUSTUNITTESTs_H

#include <QObject>
#include <QtTest/QtTest>
#include "Exhaust.h"

class ExhaustUnitTests : public QObject
{
    Q_OBJECT
public:
    ExhaustUnitTests();

private slots:
    void testDefaultConstructor();
    void testOpenExhaust();
    void testCloseExhaust();
    void testCheckIfExhaustOpened();
    void testTurnOn();
    void testTurnOff();
    void testReadFromFile();
    void testWriteToFile();
};

#endif // EXHAUSTUNITTESTs_H