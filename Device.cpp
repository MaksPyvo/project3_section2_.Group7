#include "Device.h"
Device::Device(){
    name="undefined Device";
    status=false;
    workingStatus=false;
}
Device::Device(string name, bool status, bool workingStatus){
    this->name=name;
    this->status=status;
    this->workingStatus=workingStatus;
}
void Device::turnOn()// Sets status of the Device to on (true)
{
    this->status=true;
}
void Device::turnOff()// Sets status of the Device to off (false).
{
    this->status=false;
}
void Device::setWorkingStatusWorking()// Sets workingStatus of the Device to working (true).
{
    this->workingStatus=true;
}
void Device::setWorkingStatusIdle()//Sets workingStatus of the Device to idle (false).
{
    this->workingStatus=false;
}
void Device::setNameOfDevice (string name)//Sets name to a string given as a parameter
{
    this->name=name;
}
bool Device::getStatus()//returns status of Device as a bool.
{
    return this->status;
}
bool Device::getWorkingStatus()//returns working status of Device as a bool.
{
    return this->workingStatus;
}
string Device::getName()//returns name of Device as a string.
{
    return this->name;
}
