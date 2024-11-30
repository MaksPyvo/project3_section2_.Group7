#ifndef FANUNITTESTS_H
#define FANUNITTESTS_H

#include <QObject>
#include <QtTest/QtTest>

class FanUnitTests : public QObject
{
    Q_OBJECT
public:
    FanUnitTests();

private slots:
    void testDefaultConstructor();
    void testSetSpeedLevelValidInput();
    void testSetSpeedLevelInvalidInput();
    void testGetSpeedLevel();
    void testTurnOn();
    void testTurnOff();
    void testReadFromFile();
    void testWriteToFile();
};

#endif //FANUNITTESTSs_H
