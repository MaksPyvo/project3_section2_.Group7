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

#include <QPixmap>
#include <QDir>
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
    MoistureSensor = new Sensor();
    waterPump = new WaterPump(MoistureSensor); // Initialize wtr
    irrigation = new Irrigation(waterPump);
    MoistureCheckTimer = new QTimer(this);
    connect(MoistureCheckTimer, &QTimer::timeout, this, &MainWindow::updatePumpUI);
    MoistureCheckTimer->start(5000);
    // Disable button when initialize the main window
    ui->OpenExhaustBtn->setDisabled(true);
    ui->CloseExhaustBtn->setDisabled(true);
    ui->SpeedLowLevelCheckbox->setDisabled(true);
    ui->SpeedMediumLevelCheckbox->setDisabled(true);
    ui->SpeedHighLevelCheckbox->setDisabled(true);
    disableCheckBox();
}

MainWindow::~MainWindow()
{
    delete light;
    delete fanObj;
    delete exhaustObj;
    delete heater;
    delete waterPump;
    delete irrigation;
    delete ui;
}
//waterPump->getCurrentMoisture(moistureValue);
//waterpump
void MainWindow::on_WaterPumpSwitch_clicked()
{
    if (waterPump->getPumpStatus() == "OFF" && !ui->textEdit->toPlainText().isEmpty()) {
        waterPump->turnOn();
        // Update UI to show pump is on
        ui->WaterPumpSwitch->setStyleSheet("QPushButton { background-color: Green; color:white; }");
        ui->labelStatusWtp->setText("Water pump is ON.");
    } else {
        // Turn off the pump if the moisture level matches the desired level
        waterPump->turnOff();
        ui->WaterPumpSwitch->setStyleSheet("QPushButton { background-color: Red; color:white; }");
        ui->labelStatusWtp->setText("Water pump is OFF.");
    }
    updatePumpUI();  // Update the pump UI elements
}

//update
void MainWindow::updatePumpUI()
{
    float moistureValue = ui->textEdit->toPlainText().toFloat();
    waterPump->setDesiredMoisture(moistureValue);
    if (waterPump->getPumpStatus() == "ON") {
        // Get the current moisture value from the UI
        float currentMoisture = ui->MoistureLine->text().toFloat();
        // Check if the current moisture level matches the desired moisture level
        waterPump->checkSoilMoisture(currentMoisture);
        ui->PumpRateFlow->setValue(static_cast<int>(waterPump->getPumpRate()));
        ui->labelRate->setText(QString("Current pump rate: %1 LPM").arg(waterPump->getPumpRate()));
        ui->labelStatusIrr->setText("Irrigation ACTIVE.");
        ui->IrrigationSwitch->setStyleSheet("QPushButton { background-color: Green; color:white; }");
        ui->PumpRateFlow->setValue(100);
    }else if (waterPump->getPumpStatus() == "OFF"){
         waterPump->turnOff();
        ui->PumpRateFlow->setValue(0);
         ui->WaterPumpSwitch->setStyleSheet("QPushButton { background-color: Red; color:white; }");
         ui->labelStatusWtp->setText("Water pump is OFF.");
        ui->labelRate->setText(QString("Current pump rate: %1 LPM").arg(waterPump->getPumpRate()));
        ui->IrrigationSwitch->setStyleSheet("QPushButton { background-color: red; color:white; }");
        ui->labelStatusIrr->setText("Irrigation INACTIVE.");
        MoistureCheckTimer->stop();
    }

}
//irrigation
void MainWindow::on_IrrigationSwitch_clicked()
{
    if (waterPump->getPumpStatus()=="ON") {
        ui->IrrigationSwitch->setStyleSheet("QPushButton { background-color: Green; color:white; }");
        std::thread(&Irrigation::irrigationLoop, irrigation).detach();  // Start the irrigation loop in a separate thread
        ui->labelStatusIrr->setText("Irrigation ACTIVE.");
    } else {
        irrigation->stopIrrigation();
        ui->WaterPumpSwitch->setStyleSheet("QPushButton { background-color: Red; color:white; }");
        ui->IrrigationSwitch->setStyleSheet("QPushButton { background-color: red; color:white; }");
        ui->labelStatusIrr->setText("Irrigation INACTIVE.");
    }
}

// Heater classs
void MainWindow::on_HeaterSwitch_clicked()
{
    if (fanObj->getStatus()) return;
    //if switch is off turn on and vice versa
    if(!heater->getStatus()){
         heater->ReadFromFile();
        if(heater->getHeatFlow()<=heater->getMaxHeat() && heater->getHeatFlow()>= heater->getMinHeat()){
            if(!fanObj->getStatus()){
                heater->turnOn();
                ui->HeaterScrollBar->setVisible(true);
                ui->HeaterSwitch->setStyleSheet("QPushButton { background-color: Green; color:white; }");
                ui->HeaterStatus->setText(QString("Heat Flow:%1").arg(heater->getHeatFlow()));
                ui->HeaterScrollBar->setValue(static_cast<int>(heater->getHeatFlow()));
                heater->WriteToFile();
            }
            ui->FanSwitch->setDisabled(true);
        }
        else
        {
            flashGroupBox(ui->HeaterBox);
        }

    }
    else{
        ui->HeaterScrollBar->setVisible(false);
        heater->turnOff();
        //heater->setHeatFlow(0);
        ui->HeaterScrollBar->setValue(static_cast<int>(heater->getHeatFlow()));
        ui->HeaterSwitch->setStyleSheet("QPushButton { background-color: Red; color:white; }");
        ui->HeaterStatus->setText(QString("Heat Flow:%1").arg(heater->getHeatFlow()));
        ui->FanSwitch->setDisabled(false);
    }


}
void MainWindow::on_HeaterScrollBar_valueChanged(int value)
{
    if(heater->getStatus()){
        heater->setHeatFlow(value);
        if(heater->getStatus()){
            ui->HeaterStatus->setText(QString("Heat Flow:%1").arg(heater->getHeatFlow()));
            heater->WriteToFile();
        }
    }
}

//Light class below this

void MainWindow::on_LightButton_clicked()
{
    ui->LightError->setText(" ");
    if(!(light->getStatus())){
        light->readFromFile("Light.txt");
        if(light->getBrightness()>=light->getMinBrightness() && light->getBrightness()<= light->getMaxBrightness()){
            light->turnOn();
            enableCheckBox();
            if(light->getBrightness()>=light->getMinBrightness() && light->getBrightness()<=light->getMaxBrightness()*.3)
            {
                if(!(ui->LowBrightness->isChecked())){
                    ui->LowBrightness->click();
                    //ui->MediumBrightness->setDisabled(true);
                    //ui->HighBrightness->setDisabled(true);
                }

                setBarToLow();
                ui->LightButton->setStyleSheet("background-color: green; color: white;");
            }
            else if(light->getBrightness()>light->getMaxBrightness()*.3 && light->getBrightness()<=light->getMaxBrightness()*.6)
            {
                if(!(ui->MediumBrightness->isChecked())){
                    ui->MediumBrightness->click();
                    //ui->LowBrightness->setDisabled(true);
                    //ui->HighBrightness->setDisabled(true);
                }

                setBarToMedium();
                ui->LightButton->setStyleSheet("background-color: green; color: white;");
            }
            else if (light->getBrightness()>light->getMaxBrightness()*.6 && light->getBrightness()<=light->getMaxBrightness())
            {
                if(!(ui->HighBrightness->isChecked())){
                    ui->HighBrightness->click();
                    //ui->MediumBrightness->setDisabled(true);
                   // ui->LowBrightness->setDisabled(true);
                }
                setBarToHigh();
                ui->LightButton->setStyleSheet("background-color: green; color: white;");
            }
        }

        else{

            flashGroupBox(ui->LightBox);
            ui->LightError->setText("Error: Invalid input");
            light->turnOff();
            //light->setBrightness(0);
            //light->setMinBrightness(0);
            //light->setMaxBrightness(100);
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
            disableCheckBox();
            light->writeToFile("Light.txt");
        }

        //ui->LightButton->setStyleSheet("background-color: green; color: white;");
        ui->LightProgressBar->setValue(light->getBrightness());
        //light->writeToFile("LightOut.txt");

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

}
void MainWindow::setBarToLow(){
    ui->LightProgressBar->setStyleSheet(
        "QProgressBar::chunk {"
        "    background-color: lightblue;"
        "}");
}
void MainWindow::setBarToMedium(){
    ui->LightProgressBar->setStyleSheet(
        "QProgressBar::chunk {"
        "    background-color: yellow;"
        "}");
}
void MainWindow::setBarToHigh(){
    ui->LightProgressBar->setStyleSheet(
        "QProgressBar::chunk {"
        "    background-color: orange;"
        "}");
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
void MainWindow::on_LowBrightness_clicked(bool checked)
{
    if(checked){
        light->setBrightness(light->getMaxBrightness()*.25);
        ui->LowBrightness->setCheckState(Qt::CheckState::Checked);
        ui->MediumBrightness->setCheckState(Qt::CheckState::Unchecked);
        ui->HighBrightness->setCheckState(Qt::CheckState::Unchecked);
    }
    ui->LightProgressBar->setValue(light->getBrightness());
    setBarToLow();
    light->writeToFile("LightOut.txt");
    light->writeToFile("Light.txt");
}


void MainWindow::on_MediumBrightness_clicked(bool checked)
{
    if(checked){
        light->setBrightness(light->getMaxBrightness()*.5);
        ui->LowBrightness->setCheckState(Qt::CheckState::Unchecked);
        ui->MediumBrightness->setCheckState(Qt::CheckState::Checked);
        ui->HighBrightness->setCheckState(Qt::CheckState::Unchecked);
    }
    ui->LightProgressBar->setValue(light->getBrightness());
    setBarToMedium();
    light->writeToFile("LightOut.txt");
    light->writeToFile("Light.txt");
}


void MainWindow::on_HighBrightness_clicked(bool checked)
{
    if(checked){
        light->setBrightness(light->getMaxBrightness()*.8);

        ui->LowBrightness->setCheckState(Qt::CheckState::Unchecked);
        ui->MediumBrightness->setCheckState(Qt::CheckState::Unchecked);
        ui->HighBrightness->setCheckState(Qt::CheckState::Checked);
    }
    ui->LightProgressBar->setValue(light->getBrightness());
    setBarToHigh();
    light->writeToFile("LightOut.txt");
    light->writeToFile("Light.txt");
}


//Fan class below this
void MainWindow::on_FanSwitch_clicked()
{
    if (heater->getStatus()) return;
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
        ui->HeaterSwitch->setDisabled(false);
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
        ui->HeaterSwitch->setDisabled(true);
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
                TemperatureSensor->setReadingFileName(fileName);
                TemperatureSensor->readDataFromFile();
                if (previous_temperature == new_temperature || new_temperature==-100) {
                    timer->stop();
                    timer->deleteLater();
                }
                new_temperature=TemperatureSensor->getCurrentValue();
                previous_temperature = ui->TemperatureLine->text().toInt();
                if (previous_temperature < new_temperature) {
                    previous_temperature++;
                } else if (previous_temperature > new_temperature) {
                    previous_temperature--;
                }
                ui->TemperatureLine->setText(QString::number(previous_temperature));

            });
            timer->start(10000); // Update every second
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
                HumiditySensor->setReadingFileName(fileName);
                HumiditySensor->readDataFromFile();
                if (previous_value == new_value || new_value==-100) {
                    timer->stop();
                    timer->deleteLater();
                }
                new_value=HumiditySensor->getCurrentValue();
                previous_value = ui->HumidityLine->text().toInt();
                if (previous_value < new_value) {
                    previous_value=previous_value+5;
                } else if (previous_value > new_value) {
                    previous_value=previous_value-5;
                }
                ui->HumidityLine->setText(QString::number(previous_value));
            });
            timer->start(10000); // Update every second
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
                MoistureSensor->setReadingFileName(fileName);
                MoistureSensor->readDataFromFile();
                if (previous_value == new_value || new_value==-100) {
                    timer->stop();
                    timer->deleteLater();
                }
                new_value=MoistureSensor->getCurrentValue();
                previous_value = ui->MoistureLine->text().toInt();
                if (previous_value < new_value) {
                    previous_value++;
                } else if (previous_value > new_value) {
                    previous_value--;
                }
                ui->MoistureLine->setText(QString::number(previous_value));

            });
            timer->start(10000); // Update every second
        }
    }
    MoistureTimer->start(10000);
}


void MainWindow::UpdateIlluminationSensor()
{
    char fileName[]="Illumination.txt";
    IlluminationSensor->setReadingFileName(fileName);
    IlluminationSensor->readDataFromFile();
    int new_value=IlluminationSensor->getCurrentValue();
    if(new_value==-100){
        ui->IlluminationLine->setText("ERROR");
    }else{
        int updated_value = new_value*50;
        ui->IlluminationLine->setText(QString::number(updated_value));
    }
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
            // Reset the background color
            groupBox->setStyleSheet("");
        }

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





