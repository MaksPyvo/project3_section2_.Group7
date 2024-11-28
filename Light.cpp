//implementation of Light Class

#include "Light.h"
#include <QFile>
#include <QString>
#include <QDebug>
#include <QDir>

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
void Light::readFromFile(QString file) {
    QFile fileInput(file);

    if (!fileInput.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file:" << "LightOut.txt";
        return;
    }

    QString brightness, min, max;
    QTextStream in(&fileInput);

    // Read lines with error checking
    if (!in.atEnd()) {
        brightness = in.readLine();
    }
    if (!in.atEnd()) {
        min = in.readLine();
    }
    if (!in.atEnd()) {
        max = in.readLine();
    }

    fileInput.close();
    this->setBrightness(brightness.toInt());
    this->setMinBrightness(min.toInt());
    this->setMaxBrightness(max.toInt());
}
void Light::writeToFile(QString fileName){
    QFile fileOutPut(fileName);
    if(fileOutPut.open(QIODevice::WriteOnly|QIODevice::Text)){
        QTextStream out(&fileOutPut);
        out << this->getBrightness()<<"\n";
        out << this->getMinBrightness()<<"\n";
        out << this->getMaxBrightness()<<"\n";
        qDebug()<<"Light was saved on file.";
        fileOutPut.close();
    }
    else{
        qDebug()<<"Failed to write to LightOut.txt";
    }
}
