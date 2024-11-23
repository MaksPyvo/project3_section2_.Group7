#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Sensor.h"
#include <QTimer>
#include <QDebug>
#include "Light.h"
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
}


MainWindow::~MainWindow()
{
    delete ui;
    delete light;
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
