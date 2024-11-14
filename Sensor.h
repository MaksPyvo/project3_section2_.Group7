#ifndef SENSOR_H
#define SENSOR_H

#include <string>

using namespace std;
class Sensor {
private:
    string name;
    string unitOfMeasurement;
    string readingFileName;
    int currentValue;

public:
    // Default constructor
    Sensor();
    Sensor(string name,string unitOfMeasurement,string readingFileName, int currentValue);

    // Setters
    void setName(string name);
    void setUnitOfMeasurement(string unitOfMeasurement);
    void setReadingFileName(string readingFileName);
    void setCurrentValue(int value);

    // Getters
    int getCurrentValue();
    string getName();
    string getUnitOfMeasurement();

    // Function to read data from file
    void readDataFromFile();
};
#endif // SENSOR_H
