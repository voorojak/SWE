//@(#) Entleerer.cpp
//Vedattest

#include "Dispenser.h"

Dispenser::Dispenser(float throughput, int timeUnit, Scale * scale) : InternalDevice() {
    this->throughput_ = throughput;
    this->timeUnit_ = timeUnit;
    this->scale_ = scale;
    this->scale_->attach(this);
    value_ = 0;
}

Dispenser::~Dispenser(){
    this->scale_->detach(this);
}

void Dispenser::update() {
    if (!this->executing_) return;
    if (scale_->getWeight() <= this->value_)
        executing_ = 0;
}

bool Dispenser::execute(float amount) {
    std::cout << "Ihr Cocktail hat ein Gesamtgewicht von " << scale_->getWeight() << "g" << std::endl;
    std::cout << "Entleervorgang wird begonnen..." << std::endl;
    int delta = scale_->getWeight()-amount; // amount left in the container = current weight - how much we want to dispense
    this->value_ = (delta < 0 ? 0 : delta); // prevent delta < 0
    executing_ = 1;
    while (executing_) {
        timer_->sleep(timeUnit_);
        scale_->changeWeight(-throughput_);
    }
    std::cout << std::endl;
    std::cout << "Entleervorgang wurde beendet, bitte entnehmen Sie ihren Cocktail!" << std::endl;
    std::cout << std::endl;
    return true;
}
