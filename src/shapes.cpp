#include "shapes.h"
#include "queue.h"

void Goto::draw(Queue *pQueue)
{
    pQueue->enqueueCoordinates(x, y);
    pQueue->setPos(x, y);
}

void Line::draw(Queue *pQueue)
{

    double currentX = pQueue->x;
    double currentY = pQueue->y;
    unsigned char steps = 100;

    double dx = (x - currentX) / steps;
    double dy = (y - currentX) / steps;

    for (int i = 1; i < steps + 1; i++)
    {

        pQueue->enqueueCoordinates(currentX + i * dx, currentY + i * dy);
    }
    pQueue->setPos(currentX + steps * dx, currentY + steps * dy);
}

void Square::draw(Queue *pQueue)
{
}

void DrawState::draw(Queue *pQueue)
{
    if (state)
        pQueue->enqueueValues(65535, 65535);
    else
        pQueue->enqueueValues(65534, 65534);
}
