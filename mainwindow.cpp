#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QString>
#include "Heater.h"
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: lightblue;");
    ui->HeaterSwitch->setStyleSheet("background-color: white;");
    heater = new Heater();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete heater;
}
void MainWindow:: on_heaterProgressBar_valueChanged(int value){
    heater->setHeatFlow(value);
    ui->heatFlowLabel->setText(QString("Heat Flow: %1").arg(value));

}
void MainWindow::on_HeaterSwitch_clicked()
{
    if(heater->getStatus() == false){
        heater->turnOn();
        heater->ReadFromFile();
        ui->heaterProgressBar->setMinimum(heater->getMinHeat());
        ui->heaterProgressBar->setMaximum(heater->getMaxHeat());
        ui->heaterProgressBar->setValue(heater->getHeatFlow());
        ui->HeaterSwitch->setStyleSheet("background-color: green; color: white;");
    }
    else{
        heater->turnOff();

        heater->setHeatFlow(0.0f);
        ui->heaterProgressBar->setValue(heater->getHeatFlow());
        ui->heaterProgressBar->repaint();
        ui->HeaterSwitch->setStyleSheet("background-color: red; color: white;");

    }

    ui->heatFlowLabel->setText(QString("Heat Flow: %1").arg(heater->getHeatFlow()));
    ui->heatFlowLabel->repaint();

}


void MainWindow::on_BrighnessBar_valueChanged(int value)
{
    light->setBrightness(value);
    ui->BrighnessBar->setValue(light->getBrightness());
}

