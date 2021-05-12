#include <stdio.h>
#include <stdlib.h>

#ifndef QUEUE_H
#define QUEUE_H

class Queue
{
public:
    struct Node *front = NULL;
    struct Node *rear = NULL;

    void Enqueue(unsigned short int *data);

    void Dequeue();

    // double Pos1();

    // double Pos2();

    unsigned short int *getFirst();

    bool isEmpty();

    int Length();
};

#endif