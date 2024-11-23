#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Sensor.h"
#include <QTimer>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Initializing Sensors
    TemperatureSensor=new Sensor();
    HumiditySensor=new Sensor();
    IlluminationSensor=new Sensor();
    MoistureSensor=new Sensor();
    //Creating Timers for sensors to read from file every 10 seconds
    TemperatureTimer=new QTimer(this);
    connect(TemperatureTimer,SIGNAL(timeout()),this,SLOT(UpdateTemperatureSensor()));
    HumidityTimer=new QTimer(this);
    connect(HumidityTimer,SIGNAL(timeout()),this,SLOT(UpdateHumiditySensor()));
    MoistureTimer=new QTimer(this);
    connect(MoistureTimer,SIGNAL(timeout()),this,SLOT(UpdateMoistureSensor()));
    IlluminationTimer=new QTimer(this);
    connect(IlluminationTimer,SIGNAL(timeout()),this,SLOT(UpdateIlluminationSensor()));
    TemperatureTimer->start(10000);
    HumidityTimer->start(10000);
    MoistureTimer->start(10000);
    IlluminationTimer->start(10000);
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
        heater->ReadFromFile();
        //heater->setHeatFlow(50);
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
    heater->WriteToFile();

}
void MainWindow::on_HeaterScrollBar_valueChanged(int value)
{
    heater->setHeatFlow(value);
    qDebug()<<"setting heat flow to "<<value;
    if(heater->getStatus()){
    ui->HeaterStatus->setText(QString("Heat Flow:%1").arg(heater->getHeatFlow()));
    heater->WriteToFile();
    }
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

void MainWindow::UpdateTemperatureSensor()
{
    TemperatureTimer->stop();
    char fileName[]="Temperature.txt";
    TemperatureSensor->setReadingFileName(fileName);
    TemperatureSensor->readDataFromFile();
    int new_temperature=TemperatureSensor->getCurrentValue();
    int previous_temperature = ui->TemperatureLine->text().toInt();
    if(new_temperature==-100){
         ui->TemperatureLine->setText("ERROR");
    }else{
    if (previous_temperature != new_temperature) {
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, [=]() mutable {
            if (previous_temperature < new_temperature) {
                previous_temperature++;
            } else if (previous_temperature > new_temperature) {
                previous_temperature--;
            }
            ui->TemperatureLine->setText(QString::number(previous_temperature));

            if (previous_temperature == new_temperature) {
                timer->stop();
                timer->deleteLater();
            }
        });
        timer->start(1000); // Update every second
    }
    }
    TemperatureTimer->start(10000);
}

void MainWindow::UpdateHumiditySensor()
{
    HumidityTimer->stop();
    char fileName[]="Humidity.txt";
    HumiditySensor->setReadingFileName(fileName);
    HumiditySensor->readDataFromFile();
    int new_value=HumiditySensor->getCurrentValue();
    int previous_value = ui->HumidityLine->text().toInt();
    if(new_value==-100){
        ui->HumidityLine->setText("ERROR");
    }else{
        if (previous_value != new_value) {
            QTimer *timer = new QTimer(this);
            connect(timer, &QTimer::timeout, this, [=]() mutable {
                if (previous_value < new_value) {
                    previous_value=previous_value+5;
                } else if (previous_value > new_value) {
                    previous_value=previous_value-5;
                }
                ui->HumidityLine->setText(QString::number(previous_value));

                if (previous_value == new_value) {
                    timer->stop();
                    timer->deleteLater();
                }
            });
            timer->start(1000); // Update every second
        }

    }
    HumidityTimer->start(10000);
}


void MainWindow::UpdateMoistureSensor()
{
    MoistureTimer->stop();
    char fileName[]="Moisture.txt";
    MoistureSensor->setReadingFileName(fileName);
    MoistureSensor->readDataFromFile();
    int new_value=MoistureSensor->getCurrentValue();
    int previous_value = ui->MoistureLine->text().toInt();
    if(new_value==-100){
        ui->MoistureLine->setText("ERROR");
    }else{
        if (previous_value != new_value) {
            QTimer *timer = new QTimer(this);
            connect(timer, &QTimer::timeout, this, [=]() mutable {
                if (previous_value < new_value) {
                    previous_value++;
                } else if (previous_value > new_value) {
                    previous_value--;
                }
                ui->MoistureLine->setText(QString::number(previous_value));

                if (previous_value == new_value) {
                    timer->stop();
                    timer->deleteLater();
                }
            });
            timer->start(1000); // Update every second
        }
    }
    MoistureTimer->start(10000);
}


void MainWindow::UpdateIlluminationSensor()
{
    IlluminationTimer->stop();
    char fileName[]="Illumination.txt";
    IlluminationSensor->setReadingFileName(fileName);
    IlluminationSensor->readDataFromFile();
    int new_value=IlluminationSensor->getCurrentValue();
    int previous_value = ui->IlluminationLine->text().toInt();
    if(new_value==-100){
        ui->IlluminationLine->setText("ERROR");
    }else{
        if (previous_value != new_value) {
            QTimer *timer = new QTimer(this);
            connect(timer, &QTimer::timeout, this, [=]() mutable {
                if (previous_value < new_value) {
                    previous_value=previous_value+50;
                } else if (previous_value > new_value) {
                    previous_value=previous_value-50;
                }
                ui->IlluminationLine->setText(QString::number(previous_value));

                if (previous_value == new_value) {
                    timer->stop();
                    timer->deleteLater();
                }
            });
            timer->start(1000); // Update every second
        }
    }
    IlluminationTimer->start(10000);
}

