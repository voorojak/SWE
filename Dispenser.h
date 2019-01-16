//@(#) Entleerer.h  
//Comment by Youssef
#ifndef DISPENSER_H_H
#define DISPENSER_H_H

#include <iostream>
#include "Observer.h"
#include "InternalDevice.h"
#include "Scale.h"

/**
 * @class Dispenser
 * @brief Dispenses the current Cocktail.
 */

class Dispenser : public InternalDevice, public Observer {
public:
    /**
     * A constructor of Dispenser.
     * A more elaborate description of the constructor.
     * @param timeUnit an integer argument.
     * timeUnit is an assignment to timeUnit_ variable.
     * @param throughput an float argument.
     * throughput is an assignment to throughput_ variable.
     * @param scale get Dispenser a new Scale
     */
    Dispenser(float throughput, int timeUnit, Scale * scale);

    /**
     * @brief Destructor of Dispenser
     */
    ~Dispenser();

    /** @brief if execute is used in other classes, than you return. 
     *  if the current getWeight is smaller than Value, we set the bool executing to false.
     */
    void update();


    /**
     * cout to user the emptying.
     * set executing to true. 
     * repeat the process until executing is set to false.
     * @param amount Amount to be dispensed
     * @return true
     */
    bool execute(float amount);

private:
    /** 
     * Contains the gram per time.
     */
    float throughput_;

    /**
     * Instance variable scale_.
     * Can be used for Dispenser class to check and get the Scale.
     */
    Scale * scale_;

    /**
     * Stores information given to the execute function.
     */
    float value_;

};

#endif

