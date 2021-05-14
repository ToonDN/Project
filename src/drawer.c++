#include "drawer.h"
#include "math.h"
#include "node.h"
#include "queue.h"
#include "servos.h"
#include "figures.h"

#include "dwenguino/dwenguino_board.hpp"

const double PI = 3.141592653589793238;
const double ZERO = 0.000000000001;




Drawer::Drawer()
{
    servo1.high = 4750;
    servo1.low = 1330;
    servo1.value = 2800;
    servo1.pin = PINC0;

    servo2.high = 4750;
    servo2.low = 1330;
    servo2.value = 2800;
    servo2.pin = PINC1;

    servo_drawstate.high = 4750;
    servo_drawstate.low = 1330;
    servo_drawstate.value = 3800;
    servo_drawstate.pin = PIND2;
}

void Drawer::drawLine(double x, double y) {
    double currentX = 30;
    double currentY = 30;

    double dx = (x - currentX) / 100;
    double dy = (y - currentY) / 100;


    for (int i = 0; i < 100; i++) {
        goTo(currentX + dx, currentY + dy);
    }
}

void Drawer::enqueue(double x, double y)
{
    queue.Enqueue(x, y);
}

void Drawer::goTo(double x, double y)
{
    if (x == 0 && y == 0)
    {
        x += ZERO;
        y += ZERO;
    }
    else if (x == 0)
    {
        x = ZERO;
        y -= ZERO;
    }
    else if (y == 0)
    {
        y = ZERO;
        x -= ZERO;
    }

    double totalLen = sqrt(pow(x, 2) + pow(y, 2));
    double angle2 = acos((-pow(totalLen, 2) + pow(len1, 2) + pow(len2, 2)) / (2 * len1 * len2));

    double angle1 = atan(y / x) + acos((pow(len1, 2) + pow(x, 2) + pow(y, 2) - pow(len2, 2)) / (2 * len1 * sqrt(pow(x, 2) + pow(y, 2))));
    double a1 = 180 - (angle1 * 180 / PI) + offset1;
    double a2 = 180 - (angle2 * 180 / PI) + offset2;

    //* Set rotatetimeleft based on rotation angle
    double diff1 = abs(a1 - Drawer::servo1.angle);
    double diff2 = abs(a2 - Drawer::servo2.angle);
    if (diff1 > diff2)
    {
        rotateTimeLeft = diff1;
    }
    else
    {
        rotateTimeLeft = diff2;
    }

    servo1.rotateTo(a1);
    servo2.rotateTo(a2);
}

void Drawer::drawNext()
{
    if (rotateTimeLeft <= 0 and not queue.isEmpty())
    {
        const double pos1 = queue.Pos1();
        const double pos2 = queue.Pos2();

        if (pos1 == 10000)
        {
            rotateTimeLeft = 15;
            Set_Drawstate(true);
        }
        else if (pos1 == -10000)
        {
            rotateTimeLeft = 15;
            Set_Drawstate(false);
        }else if (pos1 ==-10001)
        {
            rotateTimeLeft = 15;
        }
        
        else
        {

            Drawer::goTo(pos1 * 82 / 100, pos2 * 82 / 100);
        }

        queue.Dequeue();
    }
    else
    {
    }
}
// draw instructions need to be ale to turn the drawer on or off
void Drawer::draw_Square(Square sq)
{
    const point c = sq.center;
    const double l = sq.length;
    const double w = sq.width;
    double x = c.posx - w / 2;
    double y = c.posy - l / 2;
    // set drawer_off
    enqueue_drawstate(false);
    enqueue(x, y);
    // set drawer_on
    // enqueue_drawstate(true);
    while (y < c.posy + l / 2) // arm: lower left -> upper left
    {
        y += sq.dx;
        enqueue(x, y);
    }
    enqueue_pauze();
    while (x < c.posx + w / 2) //arm: upper left -> upper right
    {
        x += sq.dx;
        enqueue(x, y);
    }
    enqueue_pauze();
    while (y > c.posy - l / 2) //arm: upper right -> lower right
    {
        y -= sq.dx;
        enqueue(x, y);
    }
    enqueue_pauze();
    while (x > c.posx - w / 2) //arm: lower right->lower left
    {
        x -= sq.dx;
        enqueue(x, y);
    }
    enqueue_drawstate(false);
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

void Drawer::Set_Drawstate(bool set_drawing)
{
    if (set_drawing)
    {
        this->servo_drawstate.rotateTo(0);
    }
    else
    {
        this->servo_drawstate.rotateTo(130);
    }
}

void Drawer::enqueue_pauze(){
    enqueue (-10001,0);
}
