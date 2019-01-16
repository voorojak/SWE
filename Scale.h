//@(#) Waage.h
/*!
This class is for setting the Waage
*/
//Comment by Aria Gholami
#ifndef SCALE_H_H
#define SCALE_H_H

#include "Subject.h"


/**
 * @class Scale
 * @brief Offering the function of checking the weight of ingredients
 * Offering the function of checking and changing the weight of ingredients
 */
class Scale : public Subject {
public:

/*
\brief Contructor: default
*/
Scale();

/*!
This method sets the weight null if the weight is lesser than zero,
sets the deltaweight (weight of the juice)
and sets the weight of the cup and the juice
*/
/*
\param as integer
\param v a integer
*/
void changeWeight(int v);
//!This method sets the deltaweight(weight of the juice) to null
/*
This method returns an integer.
*/
int tara();
//!This method is getter statement which you can get the weight.
/*
This method returns the weight.
*/
    int getWeight();
//! This method  is a getter statement which you can get the deltaweight.
/*
\This method returns the deltaweight
*/
    int getDelta();
private:
//!This variable is an integer.
/*!
This variable sets the weight.
*/
 int weight;
//!This variable is an integer.
/*!
This variable sets the weight of the juice.
*/
 int deltaweight;
};

#endif
