#include "math.h"
#include "constants.h"
#include "globals.h"

void valuesFromCoordinates(double x, double y, unsigned short values[2])
{
    x = x * 0.82;
    y = y * 0.82;

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
    double angle2 = acos((-pow(totalLen, 2) + pow(LEN1, 2) + pow(LEN2, 2)) / (2 * LEN1 * LEN2));

    double angle1 = atan(y / x) + acos((pow(LEN1, 2) + pow(x, 2) + pow(y, 2) - pow(LEN2, 2)) / (2 * LEN1 * sqrt(pow(x, 2) + pow(y, 2))));
    double a1 = 180 - (angle1 * 180 / PI) + OFFSET1;
    double a2 = 180 - (angle2 * 180 / PI) + OFFSET2;

    values[0] = 1330 + ((a1 / 180) * 3420);
    values[1] = 1330 + ((a2 / 180) * 3420);


    //* Set rotatetimeleft based on rotation angle
    // double diff1 = abs(a1 - Drawer::servo1.angle);
    // double diff2 = abs(a2 - Drawer::servo2.angle);
    // if (diff1 > diff2)
    // {
    //     rotateTimeLeft = diff1;
    // }
    // else
    // {
    //     rotateTimeLeft = diff2;
    // }
    // return []
}