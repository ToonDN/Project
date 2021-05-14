#ifndef NODE_H
#define NODE_H

struct Node
{
public:
    // Positions of the servos
    unsigned short value1;
    unsigned short value2;
    Node *next; // Pointer to the next node

    
};

#endif