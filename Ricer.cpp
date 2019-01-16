//@(#) Stampfer.cpp
//Comments by Vedat Oeskan

#include "Ricer.h"

Ricer::Ricer() : InternalDevice() {
}

bool Ricer::execute(float time) {
    timer_->sleep(time * 1000);
    std::cout << std::endl;
    return true;
}
