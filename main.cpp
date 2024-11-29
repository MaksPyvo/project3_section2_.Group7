#include "mainwindow.h"

#include <QApplication>
//#include <QLoggingCategory>
//#include <QCoreApplication>
#include "UnitTestHeater.h"
#include "UnitTestLight.h"
int main(int argc, char *argv[])
{
    QLoggingCategory::setFilterRules("qt.*=false");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
    //UnitTestHeater unitTestHeater;
    //QTest::qExec(&unitTestHeater, argc, argv);
    //UnitTestLight unitTestLight;
    //QTest::qExec(&unitTestLight, argc, argv);
}
