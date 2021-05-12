#ifndef NODES_H
#define NODES_H

struct PointNode
{
public:
    // Positions of the servos
    double pos1;
    double pos2;
    PointNode *next; // Pointer to the next node
};

struct LineNode
{
public:
    // Positions of the servos
    double start_x;
    double start_y;
    double end_x;
    double end_y;
    LineNode *next; // Pointer to the next node
};

struct FigureNode
{
public:
    // Positions of the servos
    char value;
    FigureNode *next; // Pointer to the next node
};

#endif