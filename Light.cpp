//implementation of Light Class

#include "Light.h"
#include <QFile>
#include <QString>
#include <QDebug>
#include <QDir>

Light::Light():brightness(0), min(0), max(100){};
void Light::setBrightness(int brightness){
    if(this->min<= brightness && brightness <= this->max){
        this->brightness = brightness;
   }

}
int Light::getBrightness(){
    return this->brightness;
}
void Light::setMinBrightness(int minBrightness){
    if(minBrightness>=0 && minBrightness<100){
        this->min = minBrightness;
    }
}
int Light::getMinBrightness(){
    return this->min;
}
void Light::setMaxBrightness(int maxBrightness){
    if(maxBrightness>=0 && maxBrightness<100){
        this->max = maxBrightness;
    }
}
int Light::getMaxBrightness(){
    return this->max;
}
void Light::readFromFile(QString file) {
    QFile fileInput(file);

    if (fileInput.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString brightness, min, max;
        QTextStream in(&fileInput);

        // Read lines with error checking
        if (!in.atEnd()) {
            brightness = in.readLine();
            min = in.readLine();
            max = in.readLine();
            fileInput.close();

            this->setMinBrightness(min.toInt());
            this->setMaxBrightness(max.toInt());
            this->setBrightness(brightness.toInt());

        }
        else{
            this->brightness=-1;
            this->max= 100;
            this->min= 0;
        }
    }
    else{
        qWarning() << "Failed to open file:" << "LightOut.txt";
        this->brightness=-1;
        this->max= 100;
        this->min= 0;
    }
}
void Light::writeToFile(QString fileName){
    QFile fileOutPut(fileName);
    if(fileOutPut.open(QIODevice::WriteOnly|QIODevice::Text)){
        QTextStream out(&fileOutPut);
        out << this->getBrightness()<<"\n";
        out << this->getMinBrightness()<<"\n";
        out << this->getMaxBrightness()<<"\n";
        fileOutPut.close();
    }
    else{
        qDebug()<<"Failed to write to LightOut.txt";
    }
}
