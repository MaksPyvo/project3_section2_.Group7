#include <iostream>
#include <math.h>
#include <QFile>
#include <QTextStream>

#include "Fan.h"

// Initialize speedLevel in the constructor
Fan::Fan() : speedLevel(0)  {}

void Fan::setSpeedLevel(int speed) {
    if (speed >= 0 && speed <= 3) {
        speedLevel = speed;
    }
}

int Fan::getSpeedLevel() {
    return speedLevel;
}

void Fan::readDataFromFile() {
    QFile file("fan-data.txt");

    bool isOpened = file.open(QIODevice::ReadOnly | QIODevice::Text);
    if (!isOpened) {
        // Handle file open error
        std::cerr << "Error opening file: 'fan-data.txt'" << std::endl;
        return;
    }

    QTextStream in(&file);
    string speedLevelStr = in.readAll().toStdString();
    speedLevel = std::stoi(speedLevelStr);
    file.close();
}


void Fan::writeDataToFile() {
    QFile file("fan-data.txt");

    bool isOpened = file.open(QIODevice::WriteOnly);
    if (!isOpened) {
        // Handle file open error
        std::cerr << "Error opening file: 'fan-data.txt'" << std::endl;
        return;
    }

    QTextStream out(&file);
    out << speedLevel;
    file.close();
}
