#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Sensor.h"
#include <QTimer>
#include <QDebug>
#include "Light.h"
#include "Fan.h"
#include "Exhaust.h"
//added
#include "WaterPump.h"
#include "IrrigationSystem.h"
#include "qnamespace.h"
#include <iostream>


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
    light = new Light;
    fanObj = new Fan();
    exhaustObj= new Exhaust();

    //added
    MoistureSensor = new Sensor();
    waterPump = new WaterPump(MoistureSensor); // Initialize wtr
    irrigation = new Irrigation(waterPump);

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
    delete light;
    delete fanObj;
    delete exhaustObj;
    delete waterPump;
    delete irrigation;
}

//waterpump
void MainWindow::on_WaterPumpSwitch_clicked()
{
    if (waterPump->getPumpStatus() == "OFF") {
        waterPump->turnOn();
        ui->textEdit->append("Water pump is ON.");
    } else {
        waterPump->turnOff();
        ui->textEdit->append("Water pump is OFF.");
    }
    updatePumpUI();  // Update the pump UI elements
}
//update
void MainWindow::updatePumpUI()
{
    ui->PumpRateFlow->setValue(static_cast<int>(waterPump->getPumpRate()));
    ui->textEdit->append(QString("Current pump rate: %1 L/min").arg(waterPump->getPumpRate()));
}
//irrigation
void MainWindow::on_IrrigationSwitch_clicked()
{
    static bool irrigationRunning = false;
    if (!irrigationRunning) {
        irrigationRunning = true;
        std::thread(&Irrigation::irrigationLoop, irrigation).detach();  // Start the irrigation loop in a separate thread
        ui->textEdit->append("Irrigation system is ACTIVE.");
    } else {
        irrigation->stopIrrigation();
        irrigationRunning = false;
        ui->textEdit->append("Irrigation system is INACTIVE.");
    }
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
    ui->LightError->setText(" ");
    if(!(light->getStatus())){
        light->turnOn();
        light->readFromFile("Light.txt");
        enableCheckBox();
        if(light->getBrightness()>0 && light->getBrightness()<=35)
        {
            if(!(ui->LowBrightness->isChecked())){
                ui->LowBrightness->click();
                ui->MediumBrightness->setDisabled(true);
                ui->HighBrightness->setDisabled(true);
            }

            ui->LightProgressBar->setStyleSheet(
                "QProgressBar::chunk {"
                "    background-color: lightblue;"
                "}");
            ui->LightButton->setStyleSheet("background-color: green; color: white;");
        }
        else if(light->getBrightness()>30 && light->getBrightness()<=60)
        {
            if(!(ui->MediumBrightness->isChecked())){
                ui->MediumBrightness->click();
                ui->LowBrightness->setDisabled(true);
                ui->HighBrightness->setDisabled(true);
            }

            ui->LightProgressBar->setStyleSheet("QProgressBar::chunk {""    background-color: yellow;""}");
            ui->LightButton->setStyleSheet("background-color: green; color: white;");
        }
        else if (light->getBrightness()>60 && light->getBrightness()<light->getMaxBrightness())
        {
            if(!(ui->HighBrightness->isChecked())){
                ui->HighBrightness->click();
                ui->MediumBrightness->setDisabled(true);
                ui->LowBrightness->setDisabled(true);
            }

            ui->LightProgressBar->setStyleSheet(
                "QProgressBar::chunk {"
                "    background-color: orange;"
                "}");
            ui->LightButton->setStyleSheet("background-color: green; color: white;");
        }

        else{

            flashGroupBox(ui->LightBox);
            ui->LightError->setText("Error: Invalid input");
            light->turnOff();
            light->setBrightness(0);
            ui->LightButton->setStyleSheet("background-color: Red; color: white;");
            if(ui->LowBrightness->isChecked()){
                ui->LowBrightness->setChecked(false);
            }
            if(ui->MediumBrightness->isChecked()){
                ui->MediumBrightness->setChecked(false);
            }
            if(ui->HighBrightness->isChecked()){
                ui->HighBrightness->setChecked(false);
            }
            ui->LightProgressBar->setValue(light->getBrightness());
        }

        //ui->LightButton->setStyleSheet("background-color: green; color: white;");
        ui->LightProgressBar->setValue(light->getBrightness());
    }
    else{

        light->turnOff();
        light->setBrightness(0);
        disableCheckBox();
         ui->LightButton->setStyleSheet("background-color: Red; color: white;");
        if(ui->LowBrightness->isChecked()){
             ui->LowBrightness->setChecked(false);
        }
        if(ui->MediumBrightness->isChecked()){
            ui->MediumBrightness->setChecked(false);
        }
        if(ui->HighBrightness->isChecked()){
            ui->HighBrightness->setChecked(false);
        }
        ui->LightProgressBar->setValue(light->getBrightness());

    }
    light->writeToFile();
}
void MainWindow::enableCheckBox(){
    ui->LowBrightness->setDisabled(false);
    ui->MediumBrightness->setDisabled(false);
    ui->HighBrightness->setDisabled(false);
}
void MainWindow::disableCheckBox(){
    ui->LowBrightness->setDisabled(true);
    ui->MediumBrightness->setDisabled(true);
    ui->HighBrightness->setDisabled(true);
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
        fanObj->changeTemperature();

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
        fanObj->changeTemperature();
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
        fanObj->changeTemperature();
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
        // Turn on exhaust device
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
        
void MainWindow::flashGroupBox(QGroupBox *groupBox) {
    int count = 0;
    QTimer *timer = new QTimer(this);

    // Connect the timeout signal to the lambda
    connect(timer, &QTimer::timeout, this, [groupBox, count, timer]() mutable {
        if (count % 2 == 0) {
            // Set background color to red
            groupBox->setStyleSheet("QGroupBox { background-color: red; }");
        } else {
            
        }
        // Reset the background color
            groupBox->setStyleSheet("");
            // Increment the count
            count++;
       // qDebug() << "Flashing: " << count;
        // Stop the timer after 6 toggles (3 flashes)
        if (count >= 6) {
            timer->stop();  // Stop the timer
            groupBox->setStyleSheet(""); // Ensure the default style is restored
            timer->deleteLater();  // Clean up the timer
        }
    });

    // Start the timer with a 500 ms interval
    timer->start(500);
}
