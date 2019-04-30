/**
 * @file CarImpl.c
 * @author Xiangyuan Lian
 * @date June 2018
 * @brief File containing implementation of data struct
 */

#include "carAPI.h"

Car *initializeCar()
{
    Car *c;

    c = malloc(sizeof(Car));

    if(c == NULL)
    {
        return NULL;
    }
    c->heading = ' ';
    c->going = ' ';
    c->approchTime = 0;
    c->reachFrontTime = -1;
    c->waitTime = -1;

    return c;
}
