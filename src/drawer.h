#include "servos.h"
#include "queue.h"
#include "figures.h"

#ifndef DRAWER_H
#define DRAWER_H

class Drawer
{
public:    
    const double len1 = 13 / 0.277;
    const double len2 = 14.7 / 0.277;

    const double offset1 = 0;
    const double offset2 = 0;


    int rotateTimeLeft = 0; // Clock cycles left until the servos may rotate again
    bool hasChanged = false; // Value to determine if the rotateTimeLeft has been modified this clock cycle

    Queue queue = Queue();

    void goTo(Servo& servo1, Servo& servo2, double x, double y);

    void draw_Square(Servo& servo1, Servo& servo2, Square sq);

    void draw_Circle(Servo& servo1, Servo& servo2, Circle cir);

    void draw_2deg_Bezier(Servo& servo1, Servo& servo2, Bezier bez);
    
    void straightLineTo(double x, double y);

    void drawNext(Servo& servo1, Servo& servo2);
};
#endif