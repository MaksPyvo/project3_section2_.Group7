#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "Sensor.h"
#include "Heater.h"
#include "Light.h"
#include <QGroupBox>
#include "Fan.h"
#include "Exhaust.h"
#include "WaterPump.h"
#include "IrrigationSystem.h"

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
    void on_WaterPumpSwitch_clicked();  // Slot for water pump switch
    void on_IrrigationSwitch_clicked();  // Slot for irrigation switch
    void on_HeaterScrollBar_valueChanged(int value);
    void on_OpenExhaustBtn_clicked();
    void on_CloseExhaustBtn_clicked();
    void on_SpeedLowLevelCheckbox_clicked(bool checked);
    void on_SpeedMediumLevelCheckbox_clicked(bool checked);
    void on_SpeedHighLevelCheckbox_clicked(bool checked);
    void on_LowBrightness_clicked(bool checked);

    void on_MediumBrightness_clicked(bool checked);

    void on_HighBrightness_clicked(bool checked);
    void setBarToLow();
    void setBarToMedium();
    void setBarToHigh();

public slots:
    void UpdateTemperatureSensor();
    void UpdateHumiditySensor();
    void UpdateIlluminationSensor();
    void UpdateMoistureSensor();
    void flashGroupBox(QGroupBox *groupBox);
    void enableCheckBox();
    void disableCheckBox();
    void updatePumpUI();  // Slot to update the pump UI

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
    Light *light;
    Fan *fanObj;
    Exhaust *exhaustObj;
    WaterPump *waterPump;  // WaterPump object
    Irrigation *irrigation;  // Irrigation object
    QTimer *timer;
};

#endif // MAINWINDOW_H
