#include <stddef.h>
#include <stdlib.h>
#include "queue.h"
#include "node.h"
#include "dwenguino/dwenguino_board.hpp"

bool Queue::isEmpty()
{
    // Returns true if the first and last pointers are null because this indicates that the que is empty
    return (first == NULL && last == NULL);
};

void Queue::add(const double pos1, const double pos2)
{
    
    Node node = Node(); // Creates a pointer to a new node
    node.pos1 = pos1;
    node.pos2 = pos2;

    Node *p; // Pointer to new node
    p = &node;

    if (first == NULL)
    {
        // Set both pointers because the queue had at most one node
        first = p;
        last = p;
    }
    else
    {
        // If the queue had more than one node, set the next pointer currently last node to our newly created node
        last->next = p;

        // Now set the last node equal to our newly created node
        last = p;
    }
}

void Queue::remove()
{
    if (first == NULL)
    {
        free(first); // Clear the memory used by the first node
        first = last = NULL;
    }
    else
    {
        // If the queue had more than one node

        Node *p = first;     // Store the pointer to the first node
        first = first->next; // Set the first node equal to the node it is pointing to
        free(p);             // Clear the memory of pointer to the previously first node
    }
}

Node Queue::getFirst()
{
    return *first; // Return the first node
}

Node Queue::getLast()
{
    return *last; // Return the last node
};