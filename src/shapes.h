#include "queue.h"

#ifndef SHAPES_H
#define SHAPES_H

class Shape
{
public:
    virtual void draw(Queue *pQueue) = 0;
};

struct Goto : Shape
{
    double x, y;
    Goto(double _x, double _y) : x(_x), y(_y) {}

    void draw(Queue *pQueue);
};

struct Line : Shape
{
    double x, y;
    Line(double _x, double _y) : x(_x), y(_y) {}

    void draw(Queue *pQueue);
};

struct Square : Shape
{
    double topleftX, topleftY, bottomrightX, bottomrightY;
    Square(double _topleftX, double _topleftY, double _bottomrightX, double _bottomrightY)
        : topleftX(_topleftX), topleftY(_topleftY), bottomrightX(_bottomrightX), bottomrightY(_bottomrightY) {}

    void draw(Queue *pQueue);
};

struct DrawState : Shape
{
    const bool state;
    DrawState(const bool _state) : state(_state) {}

    void draw(Queue *pQueue);
};

struct Zero : Shape
{
    double x, y;
    Zero(double _x, double _y) : x(_x), y(_y) {}

    void draw(Queue *pQueue);
};

struct One : Shape
{
    double x, y;
    One(double _x, double _y) : x(_x), y(_y) {}

    void draw(Queue *pQueue);
};

#endif