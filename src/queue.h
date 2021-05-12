#include<stdio.h>
#include<stdlib.h>

#ifndef QUEUE_H
#define QUEUE_H

class Queue
{
public:
    struct Node *front = NULL;
    struct Node *rear = NULL;

    void Enqueue(struct Node *node);

    void Dequeue();

    // double Pos1();

    // double Pos2();

    struct Node getFirst();

    bool isEmpty();

    int Length();
};

#endif