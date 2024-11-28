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
    if(heat>=getMinHeat() && heat<=getMaxHeat()){
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
    int heat=0, min=0, max= 0;
    QFile file("Heater.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&file);
        if(!in.atEnd()){
            heat = in.readLine().toInt();
            min = in.readLine().toInt();
            max = in.readLine().toInt();
        }
        file.close();
        this->setHeatFlow(heat);
        this->setMinHeat(min);
        this->setMaxHeat(max);
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
