//@(#) Timer.h
/*!
This class is for setting the Timer of the device
 */
//Comment by Aria Gholami
#ifndef TIMER_H_H
#define TIMER_H_H

#include <ctime>
#include <iostream>

/**
 * @class Timer
 * @brief Offerings the common functions of a timer
 * Offering the common functions of a timer like sleeping, setting etc.
 */
class Timer {
public:
    /**
     * Constant variable that represents the turbo being enabled.
     */
    static const int TURBO_ON = 1000;
    
    /**
     * Constant variable that represents the turbo being disabled.
     */
    static const int TURBO_OFF = 10;
    
    //! This method is for setting the turbo.
    /*
    \param turbo an integer
     */
    void setTurbo(int trbo);
    
    //! This static pointer method Timer is for setting a new Timer.
    static Timer * getInstance();

    /**
     * 	~Timer( )
     *     {
     *         instanceFlag = false;
     *     };
     */

    //!This method is for running the Timer.
    /*
    \param millisecond a long
     */
    void sleep(long milliseconds);

private:
    //!This varibale is using for knowing when a instance is chosen.
    /*
    instanceFlag is a static bool
     */
    static bool instanceFlag;
    //! This variable is the Timer which show how long the drinks still takes.
    /*
    timer is a static Timer pointer
     */
    static Timer * timer;
    //! This variable is the turbo which control the speed of the Timer.
    /*
    turbo is a integer variable
     */
    int turbo;

    Timer() : turbo(10), timeCounter(0), lastTime(0), thisTime(0) {
    };
    //! This variable sets the Time when we want get a new counter ("*").
    /*
    \double variable
     */
    double timeCounter;

    std::clock_t lastTime;

    std::clock_t thisTime;


};

#endif
