#include <iostream>
#include <math.h>
#include <QFile>
#include <QTextStream>

#include "Exhaust.h"

Exhaust::Exhaust() : isOpened(false) {}

void Exhaust::openExhaust() {
    isOpened = true;
}

void Exhaust::closeExhaust() {
    isOpened = false;
}

bool Exhaust::checkIfExhaustOpened() {
    return isOpened;
}

void Exhaust::readDataFromFile() {
    QFile file("exhaust-data.txt");

    bool fileOpened = file.open(QIODevice::ReadOnly | QIODevice::Text);
    if (!fileOpened) {
        // Handle file open error
        std::cerr << "Error opening file: 'fan-data.txt'" << std::endl;
        return;
    }

    QTextStream in(&file);
    string isOpenedStr = in.readAll().toStdString();
    isOpened = std::stoi(isOpenedStr);
    file.close();
}


void Exhaust::writeDataToFile() {
    QFile file("exhaust-data.txt");

    bool fileOpened = file.open(QIODevice::WriteOnly);
    if (!fileOpened) {
        // Handle file open error
        std::cerr << "Error opening file: 'fan-data.txt'" << std::endl;
        return;
    }

    QTextStream out(&file);
    out << isOpened;
    file.close();
}
