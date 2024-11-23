//Heater implementation

#include "Heater.h"
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDebug>
Heater::Heater(){

    this->heatFlow =0;
    this->maxHeatFlow =100;
    this->minHeatFlow = 0;
}
Heater::Heater(int currentHeat, int maximum, int minimum){
    this->heatFlow = currentHeat;
    this->maxHeatFlow= maximum;
    this->minHeatFlow = minimum;

}
void Heater::setHeatFlow(int heat){
    if(heat>=getMinHeat() && heat<getMaxHeat()){
        this->heatFlow = heat;
    }
}
int Heater::getHeatFlow(){
    return this->heatFlow;
}
void Heater::setMaxHeat(int max){
    this->maxHeatFlow = max;
}
int Heater::getMaxHeat(){
    return this->maxHeatFlow;
}
void Heater::setMinHeat(int min){
    this->minHeatFlow = min;
}
int Heater::getMinHeat(){
    return this->minHeatFlow;
}
void Heater::ReadFromFile(){
    QString heat, min, max;
    QFile file("Heater.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&file);
        if(!in.atEnd()){
            heat = in.readLine();
            min = in.readLine();
            max = in.readLine();
        }
        file.close();
        this->setHeatFlow(heat.toInt());
        this->setMinHeat(min.toInt());
        this->setMaxHeat(max.toInt());
    }

    else{
        qDebug()<<"ERROR: Reading Heater data to file";
    }

}

void Heater::WriteToFile(){
    QFile fileOutPut("Temperature.txt");
    if(fileOutPut.open(QIODevice::WriteOnly|QIODevice::Text)){
        QTextStream out(&fileOutPut);
        out<<this->getHeatFlow()<<"\n";
        out<<this->getMinHeat()<<"\n";
        out<<this->getMaxHeat()<<"\n";
        fileOutPut.close();
    }
    else{
        qDebug()<<"ERROR: saving Heater data to file";
    }
}
