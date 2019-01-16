//@(#) Dosierer.h

#ifndef DOSER_H_H
#define DOSER_H_H

#include <string>
#include <iostream>

#include "Observer.h"
#include "InternalDevice.h"
#include "Scale.h"

/**
 * @class Doser
 * @brief Models a doser that contains a given ingredient
 * 
 * The Doser can dispense a given amount of its ingredients.
 */
class Doser : public InternalDevice, public Observer {
public:
    /**
     * @brief Constructor of Doser
     * @param weight Dispensing amount in gram per given time unit
     * @param timeUnit Time unit used for dispensing speed
     * @param ingredient Ingredient within the doser
     * @param scale Scale used to measure the dispensed amount
     */
    Doser(float weight, int timeUnit, std::string ingredient, Scale * scale);
    
    /**
     * @brief Destructor of Doser
     */
    ~Doser();
    
    /**
     * @brief Checks if the dispensed amount has surpassed a threshold, stops the dispensing process if surpassed
     */
    virtual void update();

    /**
     * @brief Dispenses a given amount of the stored ingredient
     * @param weight Amount to be dispensed
     * @return true
     */
    bool execute(float weight);
    
    /**
     * @brief Add a amount of 1000 to the fillingLevel
     */
    void addFillingCapacity();
    
     /**
     * @brief Printing status of filling level
     */
    void status();

    /**
     * @brief Returns the gram per time unit
     * @return Gram per time unit
     */
    int getThroughput();

    /**
     * @brief Returns the filingLevel
     * @return fillingLevel in gram
     */
    int getFillingLevel();
    
    /**
     * Filling level of doser in gram
     */
    int fillingLevel_;    
private:
    /**
     * The gram per time unit as float.
     */
    float throughput_;

    /**
     * Instance variable for the scale to be used in measurement operations.
     */
    Scale * scale_;

    /**
     * Amount to be dispensed in one operation.
     */
    float weight_;

    /**
     * Name of the stored ingredient.
     */
    std::string ingredient_;
};

#endif
