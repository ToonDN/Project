#include <stdio.h>
#include <stdlib.h>

#ifndef POINTQUEUE_H
#define POINTQUEUE_H

class PointQueue
{
public:
    struct PointNode *front = NULL;
    struct PointNode *rear = NULL;

    void Enqueue(double pos1, double pos2);

    void Dequeue();

    double Pos1();

    double Pos2();

    bool isEmpty();

    int Length();
};
#endif