#include "point_queue.h"
#include "nodes.h"
#include <stdio.h>
#include <stdlib.h>


void PointQueue::Enqueue(double pos1, double pos2)
{
    struct PointNode *temp =
        (struct PointNode *)malloc(sizeof(struct PointNode));
    temp->pos1 = pos1;
    temp->pos2 = pos2;

    temp->next = NULL;
    if (front == NULL && rear == NULL)
    {
        front = rear = temp;
        return;
    }
    rear->next = temp;
    rear = temp;
}

void PointQueue::Dequeue()
{
    struct PointNode *temp = front;
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

double PointQueue::Pos1()
{
    return front->pos1;
}

double PointQueue::Pos2()
{
    return front->pos2;
}

bool PointQueue::isEmpty()
{
    return (front == NULL);
}

int PointQueue::Length()
{
    int result = 0;
    struct PointNode *temp = front;
    while (temp != NULL)
    {
        result++;
        temp = temp->next;
    }
    return result;
}
