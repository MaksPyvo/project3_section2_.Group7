#include "mainwindow.h"

#include <QApplication>
#include <QLoggingCategory>
#include <QCoreApplication>
#include <QtTest/QtTest>
#include "UnitTestHeater.h"
/*int main(int argc, char *argv[])
{
    QLoggingCategory::setFilterRules("qt.*=false");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    UnitTestHeater unitTestHeater;
    return QTest::qExec(&unitTestHeater, argc, argv);
    return a.exec();
}*/
int main(int argc, char *argv[]) {
    QLoggingCategory::setFilterRules("qt.*=false");
    QApplication a(argc, argv);

    // Run unit tests
    UnitTestHeater unitTestHeater;
    return QTest::qExec(&unitTestHeater, argc, argv);
}
