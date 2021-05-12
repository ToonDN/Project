#include "line_queue.h"
#include "nodes.h"
#include <stdio.h>
#include <stdlib.h>


void LineQueue::Enqueue(double start_x, double start_y, double end_x, double end_y)
{
    struct LineNode *temp =
        (struct LineNode *)malloc(sizeof(struct LineNode));
    
    temp->start_x = start_x;
    temp->start_y = start_y;
    temp->end_x = end_x;
    temp->end_y = end_y;

    temp->next = NULL;
    if (front == NULL && rear == NULL)
    {
        front = rear = temp;
        return;
    }
    rear->next = temp;
    rear = temp;
}

void LineQueue::Dequeue()
{
    struct LineNode *temp = front;
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

double LineQueue::StartX()
{
    return front->start_x;
}

double LineQueue::StartY()
{
    return front->start_y;
}
double LineQueue::EndX()
{
    return front->end_x;
}
double LineQueue::EndY()
{
    return front->end_y;
}

bool LineQueue::isEmpty()
{
    return (front == NULL);
}

int LineQueue::Length()
{
    int result = 0;
    struct LineNode *temp = front;
    while (temp != NULL)
    {
        result++;
        temp = temp->next;
    }
    return result;
}