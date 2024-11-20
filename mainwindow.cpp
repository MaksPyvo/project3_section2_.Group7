#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Fan.h"
#include "Exhaust.h"
#include "qnamespace.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fanObj = new Fan();
    exhaustObj= new Exhaust();

    // Disable button when initialize the main window
    ui->OpenExhaustBtn->setDisabled(true);
    ui->CloseExhaustBtn->setDisabled(true);
    ui->SpeedLowLevelCheckbox->setDisabled(true);
    ui->SpeedMediumLevelCheckbox->setDisabled(true);
    ui->SpeedHighLevelCheckbox->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete fanObj;
    delete exhaustObj;
}
// Heater classs
void MainWindow::on_HeaterSwitch_clicked()
{

}
//Light class below this

void MainWindow::on_LightButton_clicked()
{

}

//Fan class below this
void MainWindow::on_FanSwitch_clicked()
{
    if (fanObj->getStatus()) {
        // Turn off exhaust device
        fanObj->writeDataToFile();
        fanObj->turnOff();

        // Disable all checkboxes
        ui->SpeedLowLevelCheckbox->setDisabled(true);
        ui->SpeedMediumLevelCheckbox->setDisabled(true);
        ui->SpeedHighLevelCheckbox->setDisabled(true);

        // Uncheck all checkboxes
        ui->SpeedLowLevelCheckbox->setCheckState(Qt::CheckState::Unchecked);
        ui->SpeedHighLevelCheckbox->setCheckState(Qt::CheckState::Unchecked);
        ui->SpeedMediumLevelCheckbox->setCheckState(Qt::CheckState::Unchecked);

        // Change switch button color
        ui->FanSwitch->setStyleSheet("background-color: red; color: white;");
    }
    else {
        // Turn on Fan
        fanObj->turnOn();
        fanObj->readDataFromFile();

        // Enable all checkboxes
        ui->SpeedLowLevelCheckbox->setDisabled(false);
        ui->SpeedMediumLevelCheckbox->setDisabled(false);
        ui->SpeedHighLevelCheckbox->setDisabled(false);

        // Check previous speed level when turn on Fan
        int speedLevel = fanObj->getSpeedLevel();
        if (speedLevel == 1) ui->SpeedLowLevelCheckbox->setCheckState(Qt::CheckState::Checked);
        if (speedLevel == 2) ui->SpeedMediumLevelCheckbox->setCheckState(Qt::CheckState::Checked);
        if (speedLevel == 3) ui->SpeedHighLevelCheckbox->setCheckState(Qt::CheckState::Checked);

        // Change switch button color
        ui->FanSwitch->setStyleSheet("background-color: green; color: white;");
    }
}

void MainWindow::on_SpeedLowLevelCheckbox_clicked(bool checked)
{
    if (checked) {
        fanObj->setSpeedLevel(1);
        ui->SpeedLowLevelCheckbox->setCheckState(Qt::CheckState::Checked);
        ui->SpeedMediumLevelCheckbox->setCheckState(Qt::CheckState::Unchecked);
        ui->SpeedHighLevelCheckbox->setCheckState(Qt::CheckState::Unchecked);
    }
    else {
        fanObj->setSpeedLevel(0);
        ui->SpeedLowLevelCheckbox->setCheckState(Qt::CheckState::Unchecked);
    }
}


void MainWindow::on_SpeedMediumLevelCheckbox_clicked(bool checked)
{
    if(checked) {
        fanObj->setSpeedLevel(2);
        ui->SpeedLowLevelCheckbox->setCheckState(Qt::CheckState::Unchecked);
        ui->SpeedMediumLevelCheckbox->setCheckState(Qt::CheckState::Checked);
        ui->SpeedHighLevelCheckbox->setCheckState(Qt::CheckState::Unchecked);
    }
    else {
        fanObj->setSpeedLevel(0);
        ui->SpeedMediumLevelCheckbox->setCheckState(Qt::CheckState::Unchecked);
    }
}


void MainWindow::on_SpeedHighLevelCheckbox_clicked(bool checked)
{
    if(checked) {
        fanObj->setSpeedLevel(3);
        ui->SpeedLowLevelCheckbox->setCheckState(Qt::CheckState::Unchecked);
        ui->SpeedMediumLevelCheckbox->setCheckState(Qt::CheckState::Unchecked);
        ui->SpeedHighLevelCheckbox->setCheckState(Qt::CheckState::Checked);
    }
    else {
        fanObj->setSpeedLevel(0);
        ui->SpeedHighLevelCheckbox->setCheckState(Qt::CheckState::Unchecked);
    }
}

void MainWindow::on_ExhaustSwitch_clicked()
{
    if (exhaustObj->getStatus()) {
        // Turn off exhaust device
        exhaustObj->writeDataToFile();
        exhaustObj->turnOff();

        // Update UI
        ui->OpenExhaustBtn->setDisabled(true);
        ui->CloseExhaustBtn->setDisabled(true);
        ui->ExhaustSwitch->setStyleSheet("background-color: red; color: white;");
    }
    else {
        exhaustObj->turnOn();
        exhaustObj->readDataFromFile();

        // Update UI
        if(exhaustObj->checkIfExhaustOpened()) {
            ui->OpenExhaustBtn->setDisabled(true);
            ui->CloseExhaustBtn->setDisabled(false);
        }
        else {
            ui->OpenExhaustBtn->setDisabled(false);
            ui->CloseExhaustBtn->setDisabled(true);
        }
        ui->ExhaustSwitch->setStyleSheet("background-color: green; color: white;");
    }
}

void MainWindow::on_OpenExhaustBtn_clicked()
{
    exhaustObj->openExhaust();
    ui->OpenExhaustBtn->setDisabled(true);
    ui->CloseExhaustBtn->setDisabled(false);
}


void MainWindow::on_CloseExhaustBtn_clicked()
{
    exhaustObj->closeExhaust();
    ui->OpenExhaustBtn->setDisabled(false);
    ui->CloseExhaustBtn->setDisabled(true);
}


//Water below this
void MainWindow::on_WaterPumpSwitch_clicked()
{

}


void MainWindow::on_IrrigationSwitch_clicked()
{

}
//sesors below this

void MainWindow::on_TemperatureInput_textChanged()
{

}
