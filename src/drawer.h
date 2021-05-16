#include "servos.h"
#include "figures.h"
#include "queue.h"
#include "shapes.h"
#include "dwenguino/dwenguino_board.hpp"

#ifndef DRAWER_H
#define DRAWER_H

class Drawer
{
public:
    Drawer();

    Servo servo1 = Servo(1330, 4750, PINC0);
    Servo servo2 = Servo(1330, 4750, PINC1);
    Servo servoDrawstate = Servo(1330, 4750, PIND2);

    Queue queue = Queue();

    unsigned short current_x, current_y = 0;

        int rotateTimeLeft = 100; // Clock cycles left until the servos may rotate again

    void draw_Square(Square sq);

    void draw_Circle(Circle cir);
    // step 1: for x= center-radius -->center+radius
    // (x,y) ---> (x+dx, y+ (x-center)*dx)/(sqrt(radius^2-(x-center)^2))
    // step 2: for x= center+radius --> center-radius
    // (x,y) ---> (x-dx, y- (x-center)*dx)/(sqrt(radius^2-(x-center)^2))

    void draw_2deg_Bezier(Bezier bez);

    void gotoValues(unsigned short v1, unsigned short v2);
    void gotoCoordinates(double x, double y);

    void drawLine(double x, double y);
    void drawNext();

    void enqueue(double x, double y);
    void Set_Drawstate(bool set_drawing);

    void enqueue_drawstate(bool state);
    void enqueue_pauze();

    void enqueueShape(Shape *shape);
};
#endif