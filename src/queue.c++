#include "queue.h"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>

struct Node *front = NULL;
struct Node *rear = NULL;

void Queue::Enqueue(double pos1, double pos2)
{

    // while (length > 300)
    // {
    //     _delay_ms(20);
    // };

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

    length++;
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
    length--;
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

