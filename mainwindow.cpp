#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
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



