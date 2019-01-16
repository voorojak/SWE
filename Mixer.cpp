//@(#) Mixer.cpp HALLO 
//Comments by Vedat Oeskan


#include "Mixer.h"

Mixer::Mixer() : InternalDevice() {

}

bool Mixer::execute(float time) {
    timer_->sleep(time * 1000);
    std::cout << std::endl;
    return true;
}
