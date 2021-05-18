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

    const double r = radius;
    double x = x_cen - r + ZERO;
    double y = y_cen;
    // set drawer_off
    DrawState(false).draw(pQueue);
    Goto(x, y).draw(pQueue);
    //set_drawer_on
    while (x < x_cen + r) // position +180 -> +0
    {
        x += dx;
        if (x == r + x_cen) //avoid singularities
        {
            x += ZERO;
        }

        y += -(x - x_cen) * dx / sqrt(r * r - (x - x_cen) * (x - x_cen));
        pQueue->enqueueCoordinates(x, y);
    }
    while (x > x_cen - r) // position -0-> -180
    {
        x -= dx;
        if (x == r - x_cen) //avoid singularities
        {
            x -= ZERO;
        }
        y += (x - x_cen) * dx / sqrt(r * r - (x - x_cen) * (x - x_cen));
        pQueue->enqueueCoordinates(x, y);
    }
    pQueue->setPos(x, y);
}
void Bezier::draw(Queue *pQueue)
{
//Bezier: = t->(1 - t) ^ 2 * P0 + 2(1 - t) *t *P1 + t ^ 2 *P2 
    // const double p0x = bez.P0.posx;
    // const double p0y = bez.P0.posy;
    // const double p1x = bez.P1.posx;
    // const double p1y = bez.P1.posy;
    // const double p2x = bez.P2.posx;
    // const double p2y = bez.P2.posy;
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
        x += (-(1 - t) * 2 * p0_x - 2 * (1 - 2 * t) * p1_x + t * 2 * p2_x) * dt;
        y += (-(1 - t) * 2 * p0_y - 2 * (1 - 2 * t) * p1_y + t * 2 * p2_y) * dt;
    }
}