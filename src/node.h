#ifndef NODE_H
#define NODE_H

struct Node
{
public:
    /**
     * @brief value corresponding with servo 1 and servo 2
     * 
     */
    unsigned short value1;
    unsigned short value2;
    /**
     * @brief // Pointer to the next node
     * 
     */
    Node *next; 

    
};

#endif