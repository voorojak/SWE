//@(#) Stampfer.h
//Comments by Vedat Oeskan

#ifndef RICER_H_H
#define RICER_H_H
#include "InternalDevice.h"

/**
 * @class Ricer
 * @brief subclass of 'InternalDevice'. Initializing the trudging of the cocktail
 *
 * subclass of 'InternalDevice'. Initializing the truding of the cocktail, which is an internal action controlled by a timer
 */

class Ricer : public InternalDevice {
public:
/**
* @brief Constructor: standard
*/
    Ricer();

/**
* @brief starting trudging process for a set time
* @param time time the device is trudging the cocktail
* @return true
*/
    bool execute(float time);

private:
};

#endif
