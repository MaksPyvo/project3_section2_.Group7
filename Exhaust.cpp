#include <iostream>
#include <math.h>
#include <QFile>
#include <QTextStream>

#include "Exhaust.h"

Exhaust::Exhaust() : isOpened(false) {}

void Exhaust::openExhaust() {
    isOpened = true;
    changeHumidityLevel();
}

void Exhaust::closeExhaust() {
    isOpened = false;
    changeHumidityLevel();
}

bool Exhaust::checkIfExhaustOpened() {
    return isOpened;
}

void Exhaust::readDataFromFile() {
    QFile file("exhaust-data.txt");

    bool fileOpened = file.open(QIODevice::ReadOnly | QIODevice::Text);
    if (!fileOpened) {
        // Handle file open error
        std::cerr << "Error opening file: 'fan-data.txt'\n" << std::endl;
        return;
    }

    QTextStream in(&file);
    string isOpenedStr = in.readLine().toStdString();
    isOpened = std::stoi(isOpenedStr);
    file.close();
    changeHumidityLevel();
}


void Exhaust::writeDataToFile() {
    QFile file("exhaust-data.txt");

    bool fileOpened = file.open(QIODevice::WriteOnly);
    if (!fileOpened) {
        // Handle file open error
        std::cerr << "Error opening file: 'fan-data.txt'\n" << std::endl;
        return;
    }

    QTextStream out(&file);
    out << isOpened;
    file.close();
}

void Exhaust::changeHumidityLevel() {
    QFile file("Humidity.txt");
    while (!file.open(QIODevice::WriteOnly)) {
        // Handle file open error
        std::cerr << "Error opening file: 'Humidity.txt'" << std::endl;
    }

    int humidity = isOpened ? 50 : 75;
    QTextStream out(&file);
    out << humidity;
    file.close();
}
