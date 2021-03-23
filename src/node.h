#ifndef NODE_H
#define NODE_H

struct Node
{
    double pos1, pos2; // Positions of the servos
    Node *next; // Pointer to the next node
};

#endif