QT       += core gui
QT += testlib
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Device.cpp \
    Exhaust.cpp \
    Fan.cpp \
    Heater.cpp \
    IrrigationSystem.cpp \
    Light.cpp \
    Sensor.cpp \
    UnitTestHeater.cpp \
    UnitTestLight.cpp \
    FanUnitTests.cpp \
    ExhaustUnitTests.cpp \
    WaterPump.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Device.h \
    Exhaust.h \
    Fan.h \
    Heater.h \
    IrrigationSystem.h \
    Light.h \
    Sensor.h \
    UnitTestHeater.h \
    UnitTestLight.h \
    FanUnitTests.h \
    ExhaustUnitTests.h \
    WaterPump.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
