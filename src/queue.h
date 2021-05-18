#include <stdio.h>
#include <stdlib.h>

#ifndef QUEUE_H
#define QUEUE_H

class Queue
{
public:
    /**
     * @brief first and last node of the queue
     * 
     */
    struct Node *front = NULL;
    struct Node *rear = NULL;

    /**
     * @brief length of the queue
     * 
     */
    unsigned short length = 0;
    /**
     * @brief (x,y) variables that record the current position of the pencil
     * 
     */
    double x, y;
    /**
     * @brief add values to the queue
     * 
     * @param value1 
     * @param value2 
     */
    void enqueueValues(unsigned short value1, unsigned short value2);
    /**
     * @brief add values coorsponding with (x,y) coordinates to the queue
     * 
     * @param x 
     * @param y 
     */
    void enqueueCoordinates(double x, double y);
    /**
     * @brief removes the first element of the queue
     * 
     */
    void Dequeue();
    /**
     * @brief returns de servo value for servo 1 of the first node of the queue
     * 
     * @return unsigned short 
     */
    unsigned short Value1();
    /**
     * @brief returns de servo value for servo 2 of the first node of the queue
     * 
     * @return unsigned short 
     */
    unsigned short Value2();
    /**
     * @brief return true if the queue is empty, if not it return false
     * 
     * @return true 
     * @return false 
     */
    bool isEmpty();

    /**
     * @brief update the recorded position of the pencil
     * 
     * @param x 
     * @param y 
     */
    void setPos(double x, double y);
};

#endif