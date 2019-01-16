//@(#) Subject.h
//Comment by Aria Gholami

//!class Subject
/*!
A class for all Subjects using for drinks.
*/


#ifndef SUBJECT_H_H
#define SUBJECT_H_H

#include "Observer.h"

#include <vector>
#include <iostream>

class Subject {
public:

//!This class is for pushing all observers using the machine in a vector.
/*!
\param observer an Observer pointer
*/
 void attach(Observer * observer);

//!This class is for deleting all observers which are more than once in the vector.
/*!
\param observer a Observer pointer
*/
void detach(Observer * observer);
   
//!This class is for updating all observers in the vector observer.
void notify();

private:
//!This private vector have all observer.
    std::vector<Observer *> observers;

};

#endif

