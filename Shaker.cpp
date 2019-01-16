//@(#) Schuettler.cpp
//Comments by Vedat Oeskan


#include "Shaker.h"

Shaker::Shaker() : InternalDevice() {
}

bool Shaker::execute(float time) {
    timer_->sleep(time * 1000);
    std::cout << std::endl;
    return true;
}
