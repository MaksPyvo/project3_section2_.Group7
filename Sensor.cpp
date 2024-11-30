#include "Sensor.h"
#include <QFile>
#include <QTextStream>
#include <QString>

using namespace std;

// Default constructor
Sensor::Sensor(){
    this->name="Undefined Sensor";
    this->unitOfMeasurement="undefined unit of measurement";
    this->readingFileName={0};
    this->currentValue=-1;
}
// parameterized constructor
Sensor::Sensor(string name,string unitOfMeasurement,char* readingFileName, int currentValue){
    this->name=name;
    this->unitOfMeasurement=unitOfMeasurement;
    this->readingFileName=readingFileName;
    this->currentValue=currentValue;
}


// Setters
void Sensor::setName(string name) {
    this->name = name;
}

void Sensor::setUnitOfMeasurement(string unitOfMeasurement) {
    this->unitOfMeasurement = unitOfMeasurement;
}

void Sensor::setReadingFileName(char* readingFileName) {
    this->readingFileName = readingFileName;
}

void Sensor::setCurrentValue(int value) {
    this->currentValue = value;
}

// Getters
int Sensor::getCurrentValue() {
    return currentValue;
}

string Sensor::getName(){
    return name;
}

string Sensor::getUnitOfMeasurement(){
    return unitOfMeasurement;
}

// Function to read data from file
void Sensor::readDataFromFile() {
    QFile file(readingFileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        bool check;
        QString currentValue = in.readLine();
        this->currentValue=currentValue.toInt(&check);
        if (check==false) {
            this->currentValue = -100; // Error reading value
        }
        file.close();

    } else {
        currentValue = -100; // Error opening file
    }
}
