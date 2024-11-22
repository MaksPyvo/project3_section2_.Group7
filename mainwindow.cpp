#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "Light.h"
#include <QTimer>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

void MainWindow::on_TemperatureInput_textChanged()
{

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
