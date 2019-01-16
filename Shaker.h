//@(#) Schuettler.h
//Comments Vedat Oeskan
#ifndef SHAKER_H_H
#define SHAKER_H_H

#include "InternalDevice.h"

/**
 * @class Shaker
 * @brief subclass of 'InternalDevice'. Initializing the shaking of the cocktail
 *
 * subclass of 'InternalDevice'. Initializing the shaker of the cocktail, which is an internal action controlled by a timer
 */
class Shaker : public InternalDevice {
public:
	/**
	* @brief Constructor: standard
	*/
    Shaker();

	/**
	* @brief starting trudging process for a set time
	* @param time time the device is trudging the cocktail
        * @return true
	*/
    bool execute(float time);

private:
};

#endif
