#include "mainwindow.h"

#include <QApplication>
#include "UnitTestLight.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    UnitTestLight unitTestLight;
    return QTest::qExec(&unitTestLight, argc, argv);
    return a.exec();
}
