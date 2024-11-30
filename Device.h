
#ifndef DEVICE_H
#define DEVICE_H
#include<string>


// Device class interface - made by Maksym Pyvovar - Project III
using namespace std;
class Device{
    bool status;
    bool workingStatus;
    string name;
public:
    Device(); //default constructor
    Device(string name, bool status, bool workingStatus); //parameterized constructor to intialize and set class members to the ones given as parameters
    void turnOn(); // Sets status of the Device to on (true)
    void turnOff(); // Sets status of the Device to off (false).
    void setWorkingStatusWorking();// Sets workingStatus of the Device to working (true).
    void setWorkingStatusIdle();//Sets workingStatus of the Device to idle (false).
    void setNameOfDevice (string name);//Sets name to a string given as a parameter
    bool getStatus();//returns status of Device as a bool.
    bool getWorkingStatus();//returns working status of Device as a bool.
    string getName();//returns name of Device as a string.
};
#endif // DEVICE_H
