//implementation of Light Class

#include "Light.h"


Light::Light():brightness(0), min(0), max(100){};
void Light::setBrightness(int brightness){
    this->brightness = brightness;
}
int Light::getBrightness(){
    return this->brightness;
}
void Light::setMinBrightness(int minBrightness){
    this->min = minBrightness;
}
int Light::getMinBrightness(){
    return this->min;
}
void Light::setMaxBrightness(int maxBrightness){
    this->max = maxBrightness;
}
int Light::getMaxBrightness(){
    return this->max;
}
