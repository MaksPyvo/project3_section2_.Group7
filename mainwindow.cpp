#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    heater = new Heater;
}

MainWindow::~MainWindow()
{
    delete ui;
}
// Heater classs
void MainWindow::on_HeaterSwitch_clicked()
{
    //if switch is off turn on and vice versa
    if(!heater->getStatus()){
        heater->turnOn();
       // heater->ReadFromFile();
        heater->setHeatFlow(50);
        ui->HeaterSwitch->setStyleSheet("QPushButton { background-color: Green; color:white; }");
        ui->HeaterStatus->setText(QString("Heat Flow:%1").arg(heater->getHeatFlow()));
         ui->HeaterScrollBar->setValue(static_cast<int>(heater->getHeatFlow()));
    }
    else{
        heater->turnOff();
        heater->setHeatFlow(0);
        ui->HeaterScrollBar->setValue(static_cast<int>(heater->getHeatFlow()));
        qDebug() << "Current Heat Flow after turning off:" << heater->getHeatFlow();
        ui->HeaterSwitch->setStyleSheet("QPushButton { background-color: Red; color:white; }");
        ui->HeaterStatus->setText(QString("Heat Flow:%1").arg(heater->getHeatFlow()));
    }

}
void MainWindow::on_HeaterScrollBar_valueChanged(int value)
{
    heater->setHeatFlow(value);
    ui->HeaterStatus->setText(QString("Heat Flow:%1").arg(heater->getHeatFlow()));
}

//Light class below this

void MainWindow::on_LightButton_clicked()
{

}

//Fan class below this
void MainWindow::on_FanSwitch_clicked()
{

}

void MainWindow::on_ExhaustSwitch_clicked()
{

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





