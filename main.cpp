#include "mainwindow.h"

#include <QApplication>
//#include <QLoggingCategory>
//#include <QCoreApplication>
// #include "UnitTestHeater.h"
// #include "UnitTestLight.h"
// #include "FanUnitTests.h"
// #include "ExhaustUnitTests.h"
// #include "DeviceUnitTest.h"
//#include "SensorUnitTest.h"
//#include "UnitTestWaterPump.h"
//#include "UnitTestIrrigationSystem.h"
int main(int argc, char *argv[])
{
    //QLoggingCategory::setFilterRules("qt.*=false");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
    //UnitTestHeater unitTestHeater;
    //QTest::qExec(&unitTestHeater, argc, argv);
    //UnitTestLight unitTestLight;
    //QTest::qExec(&unitTestLight, argc, argv);
    //TestWaterPump unitTestWaterPump;
    //QTest::qExec(&unitTestWaterPump, argc, argv);
    //TestIrrigationSystem unitTestIrrigationSystem;
    //QTest::qExec(&unitTestIrrigationSystem, argc, argv);
    // Fan & Exhaust unit tests
    // FanUnitTests fanTests;
    // QTest::qExec(&fanTests, argc, argv);
    // ExhaustUnitTests exhaustTests;
    // QTest::qExec(&exhaustTests, argc, argv);

    //DeviceTest unitTestDevice;
    //return QTest::qExec(&unitTestDevice, argc,argv);

    //SensorTest unitTestSensor;
    //return QTest::qExec(&unitTestSensor, argc,argv);
}
