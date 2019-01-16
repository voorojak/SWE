//InternalDevice.cpp
#include "InternalDevice.h"

/* Not used
void InternalDevice::setTimer() {}
*/
InternalDevice::InternalDevice() {
    timer_ = Timer::getInstance();
    this->executing_ = 0;
    timeUnit_  = 0;
}

void InternalDevice::clean() {
    //std::cout << "Ich putze mich..." << std::endl;
    //myTimer->sleep(500);
    //std::cout << "Ich bin fertig mit putzen!" << std::endl;
}

void InternalDevice::status() {
}

int InternalDevice::getFillingLevel() {
    return 1000; //Default value, if no filling level is availiable
}