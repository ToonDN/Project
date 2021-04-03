#include<stdio.h>
#include<stdlib.h>

#ifndef QUEUE_H
#define QUEUE_H

class Queue
{
public:
    struct Node *front = NULL;
    struct Node *rear = NULL;

    void Enqueue(double pos1, double pos2);

    void Dequeue();

    double Pos1();

    double Pos2();

    bool isEmpty();

    int Length();
};

#endif