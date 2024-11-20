#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Fan.h"
#include "Exhaust.h"

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

    void on_TemperatureInput_textChanged();

    void on_OpenExhaustBtn_clicked();

    void on_CloseExhaustBtn_clicked();

    void on_SpeedLowLevelCheckbox_clicked(bool checked);

    void on_SpeedMediumLevelCheckbox_clicked(bool checked);

    void on_SpeedHighLevelCheckbox_clicked(bool checked);

private:
    Ui::MainWindow *ui;
    Fan *fanObj;
    Exhaust *exhaustObj;
};
#endif // MAINWINDOW_H
