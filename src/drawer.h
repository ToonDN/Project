#include "servos.h"
#include "figures.h"
#include "queue.h"
#include "shapes.h"
#include "dwenguino/dwenguino_board.hpp"
#include "constants.h"

#ifndef DRAWER_H
#define DRAWER_H

class Drawer
{
public:
    /**
     * @brief Construct a new Drawer object
     * 
     */
    Drawer();
    /**
     * @brief servo controlling the first arm
     * 
     */
    Servo servo1 = SERVO1;
    /**
     * @brief servo controlling the second arm
     * 
     */
    Servo servo2 = SERVO2;
    /**
     * @brief servo crontrolling the pencil
     * 
     */
    Servo servoDrawstate = SERVO_DRAWSTATE;
    /**
     * @brief queue that contains servo values
     * 
     */
    Queue queue = Queue();

    /**
     * @brief Clock cycles left until the servos may rotate again
     * 
     */
    int rotateTimeLeft = 100; 

    void draw_Square(Square sq);

    void draw_Circle(Circle cir);
    

    void draw_2deg_Bezier(Bezier bez);
    /**
     * @brief sets the servo values
     * 
     * @param v1 servo value for servo 1
     * @param v2  servo value for servo 2
     */
    void gotoValues(unsigned short v1, unsigned short v2);
    /**
     * @brief sets the servo values corresponding with the (x,y) coordinates
     * 
     * @param x 
     * @param y 
     */
    void gotoCoordinates(double x, double y);

    void drawLine(double x, double y);
    /**
     * @brief applies the servo values of first element of the queue and removes the first element of the queue
     * 
     */
    void drawNext();

    /**
     * @brief adds servo values corresponding to (x,y) coordinates to the queue
     * 
     * @param x 
     * @param y 
     */
    //void enqueue_Coordinates(double x, double y);
    /**
     * @brief sets servo values corresponding to drawing or not drawing depending on the boolean set_drawing
     * 
     * @param set_drawing 
     */
    void Set_Drawstate(bool set_drawing);
    /**
     * @brief adds servo values to the queue corresponding to drawing or not drawing depending on the boolean state
     * 
     * @param state 
     */
    void enqueue_drawstate(bool state);
    /**
     * @brief adds servo values to the queue corresponding to a short pauze
     * 
     */
    void enqueue_pauze();
    /**
     * @brief Adds servo values to the queue to draw a figure
     * 
     * @param shape an object with the parameters of the figure that will be drawn
     */
    void enqueueShape(Shape *shape);
};
#endif