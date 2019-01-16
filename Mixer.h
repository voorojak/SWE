//@(#) Mixer.h
//Comments by Vedat Oeskan

#ifndef MIXER_H_H
#define MIXER_H_H

#include <iostream>
#include "InternalDevice.h"

/**
 * @class Mixer
 * @brief subclass of 'InternalDevice'. Initializing mixing of the cocktail
 *
 * subclass of 'InternalDevice'. Initializing mixing of the cocktail, which is an internal action controlled by a timer
 */
class Mixer : public InternalDevice {
public:
	/**
	* @brief Constructor: standard
	*/
    Mixer();

	/**
	* @brief starting mixing process for a set time
	* @param time time the device is mixing the cocktail
        * @return true
	*/
    bool execute(float time);

    
private:

};

#endif
