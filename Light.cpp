//implementation of Light Class

#include "Light.h"
#include <QFile>
#include <QString>
#include <QDebug>

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
void Light::readFromFile(QString filePath) {
    QFile fileInput(filePath);
    if (!fileInput.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file:" << filePath;
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

    // Validate and apply values
    bool ok;
    int brightnessValue = brightness.toInt(&ok);
    if (ok) {
        this->setBrightness(brightnessValue);
    } else {
        qWarning() << "Invalid brightness value in file:" << brightness;
    }

    int minValue = min.toInt(&ok);
    if (ok) {
        this->setMinBrightness(minValue);
    } else {
        qWarning() << "Invalid minimum brightness value in file:" << min;
    }

    int maxValue = max.toInt(&ok);
    if (ok) {
        this->setMaxBrightness(maxValue);
    } else {
        qWarning() << "Invalid maximum brightness value in file:" << max;
    }
}
