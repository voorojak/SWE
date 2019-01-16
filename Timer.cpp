//Timer.cpp
//Comment by Aria Gholami

#include "Timer.h"

void Timer::setTurbo(int turbo2) {
 this->turbo = turbo2;
}

Timer * Timer::getInstance() {
    if (!instanceFlag) {
        timer = new Timer();
        instanceFlag = true;
        return timer;
    } else {
        return timer;
    }
}

void Timer::sleep(long milliseconds) {
    std::clock_t limit;
    std::clock_t now = clock();
    limit = now + milliseconds * CLOCKS_PER_SEC / 1000 / turbo;
    while (limit > now) {
        thisTime = clock();
        timeCounter += (double) (thisTime - lastTime);
        lastTime = thisTime;
        if (timeCounter > (double) CLOCKS_PER_SEC / turbo) {
            timeCounter -= (double) CLOCKS_PER_SEC / turbo;
            std::cout << "*" << std::flush;
        }
        now = clock();
    }
}


bool Timer::instanceFlag = false;

Timer * Timer::timer = 0;
