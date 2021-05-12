#include "figure_queue.h"
#include "nodes.h"
#include <stdio.h>
#include <stdlib.h>

void FigureQueue::Enqueue(char value)
{
    struct FigureNode *temp =
        (struct FigureNode *)malloc(sizeof(struct FigureNode));

    temp->value = value;

    temp->next = NULL;
    if (front == NULL && rear == NULL)
    {
        front = rear = temp;
        return;
    }
    rear->next = temp;
    rear = temp;
}

void FigureQueue::Dequeue()
{
    struct FigureNode *temp = front;
    if (front == NULL)
    {
        return;
    }
    if (front == rear)
    {
        front = rear = NULL;
    }
    else
    {
        front = front->next;
    }
    free(temp);
}

char FigureQueue::getFirst()
{
    return front->value;
}

bool FigureQueue::isEmpty()
{
    return (front == NULL);
}

int FigureQueue::Length()
{
    int result = 0;
    struct FigureNode *temp = front;
    while (temp != NULL)
    {
        result++;
        temp = temp->next;
    }
    return result;
}
