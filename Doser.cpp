//@(#) Dosierer.cpp


#include "Doser.h"

Doser::Doser(float throughput, int timeUnit, std::string ingredient, Scale * scale) : InternalDevice(), ingredient_(ingredient) {
    this->throughput_ = throughput;
    this->timeUnit_ = timeUnit;
    this->weight_ = 0.0;
    this->scale_ = scale;
    this->scale_->attach(this);
    this->ingredient_ = ingredient;
    this->fillingLevel_ = 1000.00; //starting amount
}

Doser::~Doser() {
    this->scale_->detach(this);
}

void Doser::update() {
    if (!this->executing_) return;
    if (scale_->getDelta() >= weight_) {
        executing_ = false;
    }
}

bool Doser::execute(float weight) {
    this->weight_ = weight;
    scale_->tara();
    executing_ = true;
    std::cout << ingredient_ << " Ventil wurde geoeffnet" << std::endl;
    while (executing_) {
        timer_->sleep(timeUnit_);            
        scale_->changeWeight(throughput_);
        this->fillingLevel_ = this->fillingLevel_ - (int) this->throughput_;
        if(fillingLevel_ < 0 ) {
            this->fillingLevel_ = 0; //Cannot goes to minus integers. if minus, set to zero
        } 
    }
    std::cout << ingredient_ << " Ventil wurde geschlossen" << std::endl;
    std::cout << "Es wurden " << scale_->getDelta() << "g " << ingredient_ << " abgefuellt" << std::endl;
    std::cout << std::endl;
    return true;
}

int Doser::getThroughput() {
    return this->throughput_;
}

int Doser::getFillingLevel() {
    return this->fillingLevel_;
}

void Doser::status() {
    if(ingredient_ == "Limettenstuecke") {
       std::cout << this->ingredient_ << ": " << (fillingLevel_ / 10) << std::endl; 
    } else {
       std::cout << this->ingredient_ << ": " << fillingLevel_ << std::endl;
    }
}

void Doser::addFillingCapacity(){
    fillingLevel_ = fillingLevel_ + 1000;
}