//Heater implementation

#include <Heater.h>
#include <fstream>
Heater::Heater(){
    string heaterFile = "Heater.txt";
    ifstream fin;
    float heat, min, max;
    fin.open(heaterFile);
    if(fin.is_open()){
        fin>>heat;
        fin>>min;
        fin>>max;
        fin.close();
    }
    this->setMinHeat(min);
    this->setMaxHeat(max);
    this->setHeatFlow(heat);
   // this->heatFlow =0.0;
    //this->maxHeatFlow =100.0;
    //this->minHeatFlow = 20.0;
}
Heater::Heater(float currentHeat, float maximum, float minimum){
    this->heatFlow = currentHeat;
    this->maxHeatFlow= maximum;
    this->minHeatFlow = minimum;

}
void Heater::setHeatFlow(float heat){
    if(heat>getMinHeat() && heat<getMaxHeat()){
        this->heatFlow = heat;
    }
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
