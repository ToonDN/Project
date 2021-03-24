#include "servos.h"
#include "queue.h"
#include "figures.h"

#ifndef DRAWER_H
#define DRAWER_H

class Drawer
{
public: 
    Drawer();
    
    Servo servo1 = Servo();
    Servo servo2 = Servo();


    Queue queue = Queue();

    const double len1 = 13 / 0.277;
    const double len2 = 14.7 / 0.277;

    const double offset1 = 0;
    const double offset2 = 0;


    int rotateTimeLeft = 0; // Clock cycles left until the servos may rotate again
    bool hasChanged = false; // Value to determine if the rotateTimeLeft has been modified this clock cycle



    void draw_Square(Square sq);

    void draw_Circle(Circle cir);

    void draw_2deg_Bezier(Bezier bez);

    void goTo(double x, double y);
    
    void straightLineTo(double x, double y);

    void drawNext();
};
#endif