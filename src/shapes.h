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

// struct Zero : Shape
// {
//     double x, y;
//     Zero(double _x, double _y) : x(_x), y(_y) {}

//     void draw(Queue *pQueue);
// };

// struct One : Shape
// {
//     double x, y;
//     One(double _x, double _y) : x(_x), y(_y) {}

//     void draw(Queue *pQueue);
// };
/**
 * @brief structure for draweng a circle
 * 
 */
struct Circle : Shape
{
    double x_cen, y_cen;
    double radius;
    const double dx=0.05;
    Circle(double x_cen,double y_cen,double radius){}

    void draw(Queue* pQueue);
};
/**
 * @brief structure for drawing a bezier curve
 * 
 */
struct Bezier : Shape
{
    double p0_x, p0_y;
    double p1_x, p1_y;
    double p2_x, p2_y;
    const double dt =0.05;
    Bezier(double p0_x, double p0_y,double p1_x, double p1_y,double p2_x, double p2_y){}

    void draw(Queue *pQueue);
};



#endif