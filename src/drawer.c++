#include "drawer.h"
#include "math.h"
#include "node.h"
#include "queue.h"
#include "servos.h"
#include "figures.h"
#include "constants.h"
#include "globals.h"
#include "calculations.h"

#include "dwenguino/dwenguino_board.hpp"

Drawer::Drawer()
{
}

void Drawer::gotoValues(unsigned short v1, unsigned short v2)
{
    servo1.setValue(v1);
    servo2.setValue(v2);
}

void Drawer::gotoCoordinates(double x, double y)
{
    unsigned short values[2] = {3000, 3000};
    valuesFromCoordinates(x, y, values);
    gotoValues(values[0], values[1]);
}

void Drawer::drawNext()
{
    if (rotateTimeLeft <= 0 and not queue.isEmpty())
    {
        const unsigned short v1 = queue.Value1();
        const unsigned short v2 = queue.Value2();

        if (v1 == 65535 && v2 == 65535) // True drawstate
        {
            rotateTimeLeft = 50;
            Set_Drawstate(true);
        }
        else if (v1 == 65534 && v2 == 65534) // False drawstate
        {
            rotateTimeLeft = 50;
            Set_Drawstate(false);
        }
        else
        {
            Drawer::gotoValues(v1, v2);
        }
        queue.Dequeue();
    }
}
// draw instructions need to be ale to turn the drawer on or off
void Drawer::draw_Square(Square sq)
{
    // const point c = sq.center;
    // const double l = sq.length;
    // const double w = sq.width;
    // double x = c.posx - w / 2;
    // double y = c.posy - l / 2;
    // // set drawer_off
    // enqueue_drawstate(false);
    // enqueue(x, y);
    // // set drawer_on
    // // enqueue_drawstate(true);
    // while (y < c.posy + l / 2) // arm: lower left -> upper left
    // {
    //     y += sq.dx;
    //     enqueue(x, y);
    // }
    // enqueue_pauze();
    // while (x < c.posx + w / 2) //arm: upper left -> upper right
    // {
    //     x += sq.dx;
    //     enqueue(x, y);
    // }
    // enqueue_pauze();
    // while (y > c.posy - l / 2) //arm: upper right -> lower right
    // {
    //     y -= sq.dx;
    //     enqueue(x, y);
    // }
    // enqueue_pauze();
    // while (x > c.posx - w / 2) //arm: lower right->lower left
    // {
    //     x -= sq.dx;
    //     enqueue(x, y);
    // }
    // enqueue_drawstate(false);
}

void Drawer::draw_Circle(Circle c)
{
    const point o = c.center;
    const double r = c.radius;
    double x = o.posx - r + ZERO;
    double y = o.posy;
    // set drawer_off
    enqueue(x, y);
    //set_drawer_on
    while (x < o.posx + r) // position +180 -> +0
    {
        x += c.dx;
        if (x == r + o.posx) //avoid singularities
        {
            x += ZERO;
        }

        y += -(x - o.posx) * c.dx / sqrt(r * r - (x - o.posx) * (x - o.posx));
        enqueue(x, y);
    }
    while (x > o.posx - r) // position -0-> -180
    {
        x -= c.dx;
        if (x == r - o.posx) //avoid singularities
        {
            x -= ZERO;
        }
        y += (x - o.posx) * c.dx / sqrt(r * r - (x - o.posx) * (x - o.posx));
        enqueue(x, y);
    }
}

void Drawer::draw_2deg_Bezier(Bezier bez)
{
    // Bezier:= t-> (1-t)^2*P0+2(1-t)*t*P1 +t^2*P2
    const double p0x = bez.P0.posx;
    const double p0y = bez.P0.posy;
    const double p1x = bez.P1.posx;
    const double p1y = bez.P1.posy;
    const double p2x = bez.P2.posx;
    const double p2y = bez.P2.posy;
    double t = 0;

    double x = p0x;
    double y = p0y;
    //set drawer_off
    enqueue(x, y);
    //set drawer_on
    while (t < 1)
    {
        t += bez.dt;
        x += (-(1 - t) * 2 * p0x - 2 * (1 - 2 * t) * p1x + t * 2 * p2x) * bez.dt;
        y += (-(1 - t) * 2 * p0y - 2 * (1 - 2 * t) * p1y + t * 2 * p2y) * bez.dt;
    }
}

void Drawer::enqueue_drawstate(bool state)
{
    enqueue(state * 20000 - 10000, 0);
}

void Drawer::enqueueShape(Shape *shape)
{
    shape->draw(&queue);
}

void Drawer::Set_Drawstate(bool set_drawing)
{
    if (set_drawing)
    {
        servoDrawstate.setAngle(0);
    }
    else
    {
        servoDrawstate.setAngle(175);
    }
}

void Drawer::enqueue_pauze()
{
    enqueue(-10001, 0);
}
