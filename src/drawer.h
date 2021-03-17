#include "servos.h"

#ifndef DRAWER_H
#define DRAWER_H

class Drawer
{
public:    
    const double len1 = 13 / 0.277;
    const double len2 = 14.7 / 0.277;

    const double offset1 = 0;
    const double offset2 = 0;

    double que[1000];
    int queIndex = 0;

    void goTo(Servo& servo1, Servo& servo2, double x, double y);
};
#endif