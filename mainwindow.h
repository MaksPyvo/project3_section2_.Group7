#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "Sensor.h"
#include "Heater.h"
QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_HeaterSwitch_clicked();

    void on_LightButton_clicked();

    void on_FanSwitch_clicked();
    void on_ExhaustSwitch_clicked();


    void on_WaterPumpSwitch_clicked();

    void on_IrrigationSwitch_clicked();

    void on_HeaterScrollBar_valueChanged(int value);


public slots:
    void UpdateTemperatureSensor();
    void UpdateHumiditySensor();
    void UpdateIlluminationSensor();
    void UpdateMoistureSensor();

private:
    Ui::MainWindow *ui;
    Sensor *TemperatureSensor;
    Sensor *HumiditySensor;
    Sensor *IlluminationSensor;
    Sensor *MoistureSensor;
    QTimer *TemperatureTimer;
    QTimer *HumidityTimer;
    QTimer *MoistureTimer;
    QTimer *IlluminationTimer;
    Heater *heater;
};
#endif // MAINWINDOW_H
