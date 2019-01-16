//@(#) Observer.h
//Commented by Vedat Oeskan

#ifndef OBSERVER_H_H
#define OBSERVER_H_H

/**
 * @class Observer
 * @brief Abstract: template for implementing observing function
 *
 */

class Observer {
public:
/**
 * @brief pure virtual method / abstract: to be implemented with the wanted observing function
 *
 */
    virtual void update() = 0;

};

#endif
