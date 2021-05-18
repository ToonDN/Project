#include "shapes.h"
#include "queue.h"
#include "constants.h"

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
    double dy = (y - currentY) / steps;

    for (int i = 1; i < steps + 1; i++)
    {

        pQueue->enqueueCoordinates(currentX + i * dx, currentY + i * dy);
    }
    pQueue->setPos(currentX + steps * dx, currentY + steps * dy);
}

void Square::draw(Queue *pQueue)
{
    Goto(topleftX, topleftY).draw(pQueue);
    DrawState(true).draw(pQueue);
    Line(topleftX, bottomrightY).draw(pQueue);
    Line(bottomrightX, bottomrightY).draw(pQueue);
    Line(bottomrightX, topleftX).draw(pQueue);
    Line(topleftX, topleftY).draw(pQueue);
    DrawState(false).draw(pQueue);
}

void DrawState::draw(Queue *pQueue)
{
    if (state)
        pQueue->enqueueValues(65535, 65535);
    else
        pQueue->enqueueValues(65534, 65534);
}

void Circle::draw(Queue *pQueue)
{

    // set drawer_off
    double steps = radius * 15;
    DrawState(false).draw(pQueue);
    Goto(x_cen + radius, y_cen).draw(pQueue);
    DrawState(true).draw(pQueue);
    double angle = 0;

    for (double i = 0; i < steps * 1.1; i++)
    {
        angle = (double(i) / double(steps)) * 2 * PI;
        pQueue->enqueueCoordinates(x_cen + radius * cos(angle), y_cen + radius * sin(angle));
    }
    DrawState(false).draw(pQueue);

    Goto(x_cen + radius, y_cen).draw(pQueue);
    pQueue->setPos(x_cen + radius, y_cen + radius);
}

void Smiley::draw(Queue *pQueue)
{
    Circle(30, 40, 30).draw(pQueue);
    Circle(44, 27, 8).draw(pQueue);
    Circle(16, 27, 8).draw(pQueue);

    Bezier(44, 50, 30, 66, 16, 50).draw(pQueue);
    DrawState(false).draw(pQueue);
}

void Bezier::draw(Queue *pQueue)
{
    double t = 0;

    double x = p0_x;
    double y = p0_y;
    //set drawer_off
    DrawState(false).draw(pQueue);
    Goto(x, y).draw(pQueue);
    //set drawer_on
    DrawState(true).draw(pQueue);
    while (t < 1)
    {
        t += dt;
        x += (-2 * (1 - t) * p0_x - 2 * t * p1_x + 2 * (1 - t) * p1_x + 2 * t * p2_x) * dt;
        y += (-2 * (1 - t) * p0_y - 2 * t * p1_y + 2 * (1 - t) * p1_y + 2 * t * p2_y) * dt;
        pQueue->enqueueCoordinates(x, y);
    }
}