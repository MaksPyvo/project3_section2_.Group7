//Heater implementation

#include <Heater.h>

Heater::Heater(){
    this->heatFlow =0.0;
    this->maxHeatFlow =100.0;
    this->minHeatFlow = 20.0;
}
Heater::Heater(float currentHeat, float maximum, float minimum){
    this->heatFlow = currentHeat;
    this->maxHeatFlow= maximum;
    this->minHeatFlow = minimum;

}
void Heater::setHeatFlow(float heat){
    this->heatFlow = heat;
}
float Heater::getHeatFlow(){
    return this->heatFlow;
}
void Heater::setMaxHeat(float max){
    this->maxHeatFlow = max;
}
float Heater::getMaxHeat(){
    return this->maxHeatFlow;
}
void Heater::setMinHeat(float min){
    this->minHeatFlow = min;
}
float Heater::getMinHeat(){
    return this->minHeatFlow;
}
