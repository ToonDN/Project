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
    unsigned short x, y;
    Goto(unsigned short _x, unsigned short _y) : x(_x), y(_y) {}

    void draw(Queue *pQueue);
};

struct Line : Shape
{
    unsigned short x, y;
    Line(unsigned short _x, unsigned short _y) : x(_x), y(_y) {}

    void draw(Queue *pQueue);
};

struct Square : Shape
{
    unsigned short topleftX, topleftY, bottomrightX, bottomrightY;
    Square(unsigned short _topleftX, unsigned short _topleftY, unsigned short _bottomrightX, unsigned short _bottomrightY)
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
    unsigned short x, y;
    Zero(unsigned short _x, unsigned short _y) : x(_x), y(_y) {}

    void draw(Queue *pQueue);
};

struct One : Shape
{
    unsigned short x, y;
    One(unsigned short _x, unsigned short _y) : x(_x), y(_y) {}

    void draw(Queue *pQueue);
};

#endif