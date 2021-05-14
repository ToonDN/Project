#include "queue.h"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include "calculations.h"

struct Node *front = NULL;
struct Node *rear = NULL;

void Queue::enqueueValues(unsigned short value1, unsigned short value2)
{
    while (length > 300)
    {
        _delay_ms(2);
    };

    struct Node *temp =
        (struct Node *)malloc(sizeof(struct Node));

    temp->value1 = value1;
    temp->value2 = value2;

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


void Queue::enqueueCoordinates(double x, double y) {
    unsigned short values[2];
    valuesFromCoordinates(x, y, values);
    enqueueValues(values[0], values[1]);
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

unsigned short Queue::Value1()
{
    return front->value1;
}

unsigned short Queue::Value2()
{
    return front->value2;
}

bool Queue::isEmpty()
{
    return (front == NULL);
}

void Queue::setPos(double _x, double _y)
{
    x = _x;
    y = _y;
}
