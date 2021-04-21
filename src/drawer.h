#include "servos.h"
#include "figures.h"
#include "queue.h"

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

    const double dx= 0.05; // actual value to be decided
    const double dt= 0.01; // actual value to be decided

    int rotateTimeLeft = 50; // Clock cycles left until the servos may rotate again


    void draw_Square(Square sq);

    void draw_Circle(Circle cir);
    // step 1: for x= center-radius -->center+radius
    // (x,y) ---> (x+dx, y+ (x-center)*dx)/(sqrt(radius^2-(x-center)^2))
    // step 2: for x= center+radius --> center-radius
    // (x,y) ---> (x-dx, y- (x-center)*dx)/(sqrt(radius^2-(x-center)^2))

    void draw_2deg_Bezier(Bezier bez);

    void goTo(double x, double y);
    
    void straightLineTo(double x, double y);

    void drawNext();

    void enqueue(double x, double y);
};
#endif