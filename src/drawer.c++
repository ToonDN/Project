#include "servos.h"
#include "drawer.h"
#include "math.h"
#include "queue.h"
#include "node.h"

#include "dwenguino/dwenguino_board.hpp"

const double PI = 3.141592653589793238;
const double ZERO = 0.000000000001;

void Drawer::straightLineTo(double x, double y)
{
    queue.add(x, y);
}

Drawer::Drawer()
{
    servo1.high = 4750;
    servo1.low = 1330;
    servo1.value = 1330;
    servo1.pin = PINC0;

    servo2.high = 5050;
    servo2.low = 1330;
    servo2.value = 1090;
    servo2.pin = PINC1;
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

    servo1.rotateTo(a1);
    servo2.rotateTo(a2);
}

void Drawer::drawNext()
{
    if (rotateTimeLeft <= 0 && not queue.isEmpty())
    {
        rotateTimeLeft = 100;

        const double pos1 = queue.first->pos1;
        const double pos2 = queue.first->pos2;

        // servo1.rotateTo(90);
        // servo2.rotateTo(90);

        LEDS = pos1;

        Drawer::goTo(pos1, pos2);

        queue.remove();
    }
    else
    {
    }
}
