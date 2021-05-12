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
    Servo servo_drawstate= Servo();

    Queue queue = Queue();


    const double len1 = 12.5 / 0.277;
    const double len2 = 15.75 / 0.277;

    const double offset1 = 0;
    const double offset2 = 0;

    
    

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
    void Set_Drawstate( bool set_drawing);

    void enqueue_drawstate(bool state);
    void enqueue_pauze();
}
;
#endif