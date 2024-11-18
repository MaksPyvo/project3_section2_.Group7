//Heater implementation

#include "Heater.h"
#include <QFile>
#include <QTextStream>
#include <QString>
Heater::Heater(){

    this->heatFlow =70.0;
    this->maxHeatFlow =100.0;
    this->minHeatFlow = 0.0;
}
Heater::Heater(double currentHeat, double maximum, double minimum){
    this->heatFlow = currentHeat;
    this->maxHeatFlow= maximum;
    this->minHeatFlow = minimum;

}
void Heater::setHeatFlow(double heat){
    if(heat>getMinHeat() && heat<getMaxHeat()){
        this->heatFlow = heat;
    }
}
double Heater::getHeatFlow(){
    return this->heatFlow;
}
void Heater::setMaxHeat(double max){
    this->maxHeatFlow = max;
}
double Heater::getMaxHeat(){
    return this->maxHeatFlow;
}
void Heater::setMinHeat(double min){
    this->minHeatFlow = min;
}
double Heater::getMinHeat(){
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
    }
    this->setHeatFlow(heat.toDouble());
    this->setMinHeat(min.toDouble());
    this->setMaxHeat(max.toDouble());
}
