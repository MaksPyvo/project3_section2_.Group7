#include <iostream>
#include <math.h>
#include <QFile>
#include <QTextStream>

#include "Fan.h"

// Initialize speedLevel in the constructor
Fan::Fan() : speedLevel(0)  {}

void Fan::setSpeedLevel(int speed) {
    if (speed >= 0 && speed <= 3) {
        previousSpeedLevel = speedLevel;
        speedLevel = speed;
        changeTemperature();
    }
}

void Fan::changeTemperature() {
    if (speedLevel == previousSpeedLevel) return;

    QFile file("Temperature.txt");
    while (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // Handle file open error
        std::cerr << "Error opening file: 'Temperature.txt'" << std::endl;
    }

    // Read temperature data
    QTextStream in(&file);
    int temperature = in.readLine().toInt();
    int min = in.readLine().toInt();
    int max = in.readLine().toInt();
    if (speedLevel > previousSpeedLevel) {
        temperature *= 1 - (speedLevel - previousSpeedLevel) * 0.15;
    } else {
        temperature *= 1 + (previousSpeedLevel - speedLevel) * 0.2;
    }
    if(temperature < min) temperature = min;
    if(temperature > max) temperature = max;
    file.close();

    // Edit new temperature data
    while (!file.open(QIODevice::WriteOnly)) {
        // Handle file open error
        std::cerr << "Error opening file: 'Temperature.txt'" << std::endl;
    }
    QTextStream out(&file);
    out << temperature << "\n" << min << "\n" << max;
    file.close();
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
    changeTemperature();
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
