//Waage.cpp
//Comment by Aria Gholami

#include "Scale.h"

Scale::Scale() {
    weight = 0;
    deltaweight = 0;
}

void Scale::changeWeight(int v) {
 weight += v;
 if (weight < 0)
        weight = 0;
    deltaweight += v;
    notify();
}

int Scale::tara() {
    return deltaweight = 0;
}

int Scale::getWeight() {
    return weight;
}

int Scale::getDelta() {
    return deltaweight;
}
