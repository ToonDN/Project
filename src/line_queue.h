#include <stdio.h>
#include <stdlib.h>

#ifndef LINEQUEUE_H
#define LINEQUEUE_H

class LineQueue
{
public:
    struct LineNode *front = NULL;
    struct LineNode *rear = NULL;

    void Enqueue(double start_x, double start_y, double end_x, double end_y);

    void Dequeue();

    double StartX();
    double StartY();
    double EndX();
    double EndY();

    bool isEmpty();

    int Length();
};
#endif