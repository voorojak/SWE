//InternalDevice.h
#ifndef INTERNALDEVICE_H_H
#define INTERNALDEVICE_H_H

#include "Timer.h"

/**
 * @class InternalDevice
 * @brief Abstract class: superclass for device-internal actions
 *
 * Abstract class. Superclass for executing internal actions, offering a timer and cleaning action
 */
class InternalDevice {
public:
    /**
     * @brief Pure virtual function/Abstract: start an action
     * @param value starting-parameter for initializing an action
     * @return true or false depending on the success of the execution
     */
    virtual bool execute(float value) = 0;

    /**
     * @brief Print status of filling level, if availiable
     */
    virtual void status();

    /**
     * @brief returns a fillingLevel if availiable, standardvalue of 1000
     * @return fillingLevel (if availiable) or standardvalue of 1000
     */
    virtual int getFillingLevel();

    /**
     * @brief cleaning the device
     */
    void clean();


private:
    /**
     * @brief setting up internal device timer
     */
    void setTimer();


public:
    /**
     * @brief standard constructor: initializing instance of InternalDevice and variable 'executing'
     */
    InternalDevice();

protected:
    /**
     * Contains the time unit
     */
    int timeUnit_;

    /**
     * Contains current status, whether than device is doing an action (or not)
     */
    bool executing_;

    /**
     * Instance variable of class Timer.
     * Setting up a timer
     */
    Timer * timer_;
};

#endif
