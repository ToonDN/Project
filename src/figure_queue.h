#include <stdio.h>
#include <stdlib.h>

#ifndef FIGUREQUEUE_H
#define FIGUREQUEUE_H

class FigureQueue
{
public:
    struct FigureNode *front = NULL;
    struct FigureNode *rear = NULL;

    void Enqueue(char value);

    void Dequeue();

    char getFirst();

    bool isEmpty();

    int Length();
};
#endif