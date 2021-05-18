#include "drawer.h"
#include "math.h"
#include "node.h"
#include "queue.h"
#include "servos.h"
#include "constants.h"
#include "calculations.h"
#include "math.h"
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
            rotateTimeLeft = ceil(fmax(abs(servo1.value - v1), abs(servo2.value - v2)) / 70);
            gotoValues(v1, v2);

        }
        queue.Dequeue();
    }
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


