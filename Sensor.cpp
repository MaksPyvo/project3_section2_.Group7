#include "Sensor.h"
#include <fstream>
#include <iostream>

using namespace std;

// Default constructor
Sensor::Sensor(){
    this->name="Undefined Sensor";
    this->unitOfMeasurement="undefined unit of measurement";
    this->readingFileName="undefined file name";
    this->currentValue=-1;
}
// parameterized constructor
Sensor::Sensor(string name,string unitOfMeasurement,string readingFileName, int currentValue){
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

void Sensor::setReadingFileName(string readingFileName) {
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
    ifstream fin(readingFileName);
    if (fin.is_open()) {
        int currentReading;
        if (fin >> currentReading) {
            currentValue = currentReading;
        } else {
            currentValue = -100; // Error reading value
        }
        fin.close();
    } else {
        currentValue = -100; // Error opening file
    }
}
