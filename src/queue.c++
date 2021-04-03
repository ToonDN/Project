#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "queue.h"

struct Node *front = NULL;
struct Node *rear = NULL;

void Queue::Enqueue(double pos1, double pos2)
{
    struct Node *temp =
        (struct Node *)malloc(sizeof(struct Node));
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

void Queue::Dequeue()
{
    struct Node *temp = front;
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

double Queue::Pos1()
{
    return front->pos1;
}

double Queue::Pos2()
{
    return front->pos2;
}

bool Queue::isEmpty()
{
    return (front == NULL);
}

int Queue::Length()
{
    int result = 0;
    struct Node *temp = front;
    while (temp != NULL)
    {
        result++;
        temp = temp->next;
    }
    return result;
}
