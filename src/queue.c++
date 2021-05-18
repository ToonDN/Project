#include "queue.h"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include "calculations.h"
#include "constants.h"

struct Node *front = NULL;
struct Node *rear = NULL;

void Queue::enqueueValues(unsigned short value1, unsigned short value2)
{
    // Block the program if the max queue length
    while (length > MAX_QUEUE_LENGTH)
    {
        _delay_ms(2);
    };

    // Allocate memory for the new node
    struct Node *temp =
        (struct Node *)malloc(sizeof(struct Node));

    // Set the values of the new node
    temp->value1 = value1;
    temp->value2 = value2;
    temp->next = NULL;

    // Set the new value as only value if the queue is empty
    if (front == NULL && rear == NULL)
    {
        front = rear = temp;
        return;
    }

    // Set the previously last nodes pointer to the new node
    rear->next = temp;

    // Set the rear pointer to the current node
    rear = temp;

    length++;
}

void Queue::enqueueCoordinates(double x, double y)
{
    // Ease of use version to enqueue coordinates
    unsigned short values[2];
    valuesFromCoordinates(x, y, values);
    enqueueValues(values[0], values[1]);
}

void Queue::Dequeue()
{
    struct Node *temp = front;

    // Do nothing if the queue is empty
    if (front == NULL)
    {
        return;
    }

    // Clear the queue if it contains 1 item
    if (front == rear)
    {
        front = rear = NULL;
    }

    // If the queue contains more than 1 item
    // Set the front pointer the the next node
    else
    {
        front = front->next;
    }

    // Free the memory of the first node
    // Decrease the length of the queue
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
