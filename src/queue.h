#include <stdio.h>
#include <stdlib.h>

#ifndef QUEUE_H
#define QUEUE_H

class Queue
{
public:
    struct Node *front = NULL;
    struct Node *rear = NULL;

    unsigned short length = 0;
    double x, y;
    void enqueueValues(unsigned short value1, unsigned short value2);
    void enqueueCoordinates(double x, double y);

    void Dequeue();

    unsigned short Value1();

    unsigned short Value2();

    bool isEmpty();

    void setPos(double x, double y);
};

#endif