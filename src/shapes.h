#include "queue.h"

#ifndef SHAPES_H
#define SHAPES_H

class Shape
{
public:
    virtual void draw(Queue *pQueue) = 0;
};
/**
 * @brief  structure for changing the positon of the pencil to (x,y) 
 * 
 */
struct Goto : Shape
{
    double x, y;
    Goto(double _x, double _y) : x(_x), y(_y) {}

    void draw(Queue *pQueue);
};
/**
 * @brief structure for drawing a straight line to (x,y)
 * 
 */
struct Line : Shape
{
    double x, y;
    Line(double _x, double _y) : x(_x), y(_y) {}

    void draw(Queue *pQueue);
};
/**
 * @brief structure for drawing a rectangle
 * 
 */
struct Square : Shape
{
    double topleftX, topleftY, bottomrightX, bottomrightY;
    Square(double _topleftX, double _topleftY, double _bottomrightX, double _bottomrightY)
        : topleftX(_topleftX), topleftY(_topleftY), bottomrightX(_bottomrightX), bottomrightY(_bottomrightY) {}

    void draw(Queue *pQueue);
};
/**
 * @brief structure for controlling the pencil
 * 
 */
struct DrawState : Shape
{
    const bool state;
    DrawState(const bool _state) : state(_state) {}

    void draw(Queue *pQueue);
};

/**
 * @brief structure for draweng a circle
 * 
 */
struct Circle : Shape
{
    double x_cen, y_cen;
    double radius;
    Circle(double _x_cen, double _y_cen, double _radius) : x_cen(_x_cen), y_cen(_y_cen), radius(_radius) {}

    void draw(Queue *pQueue);
};
/**
 * @brief structure for drawing a bezier curve
 * 
 */

struct Smiley : Shape
{
    Smiley() {};
    void draw(Queue *pQueue);
};

struct Bezier : Shape
{
    double p0_x, p0_y;
    double p1_x, p1_y;
    double p2_x, p2_y;
    const double dt = 0.05;
    Bezier(double _p0_x, double _p0_y, double _p1_x, double _p1_y, double _p2_x, double _p2_y) : p0_x(_p0_x), p0_y(_p0_y), p1_x(_p1_x), p1_y(_p1_y), p2_x(_p2_x), p2_y(_p2_y){};

    void draw(Queue *pQueue);
};

#endif