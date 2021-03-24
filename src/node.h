#ifndef NODE_H
#define NODE_H

struct Node
{
public:
    // Positions of the servos
    double pos1;
    double pos2;
    Node *next; // Pointer to the next node
};

#endif