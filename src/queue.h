#include "node.h"

#ifndef QUEUE_H
#define QUEUE_H

class Queue
{

public:
    Node *first;    // Pointer to first node
    Node *last;     // Pointer to last node
    bool isEmpty(); // Returns true if the queue is empty

    void add(double pos1, double pos2); // Adds a node to the queue

    void remove(); // Removes a node from the queue

    Node getFirst(); // Returns the first node in the queue

    Node getLast(); // Returns the last node in the queue
};

#endif