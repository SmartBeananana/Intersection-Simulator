/**
 * @file carAPI.h
 * @author Xiangyuan Lian
 * @date June 2018
 * @brief File containing the function definitions of struct data type car
 */
#include "LinkedListAPI.h"
#ifndef _CAR_API_
#define _CAR_API_

#include <stdio.h>
#include <stdlib.h>

/**
*Struct type data that for the data in node. Contain actual data of each car.
**/
typedef struct carInfoStruct{
    char heading;
    char going;
    double approchTime;
    double reachFrontTime;
    double waitTime;
} Car;

/**Function for creating data struct for a nodd. This data contains generic data and may be connected to
other notes in a list.
*@pre data should be of same size of void pointer on the users machine to avoid size conflicts. data must be valid.
*data must be cast to void pointer before being added.
*@post data is valid to be added to a queue
*@return On success returns a data struct Car that can be added to a node.
**/
Car *initializeCar();

#endif
