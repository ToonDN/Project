#include "math.h"
#include "constants.h"

void valuesFromCoordinates(double x, double y, unsigned short values[2])
{
    // Set deadzone in the top right corner because it is impossible to get there
    if (y < 12 && x < 7)
    {
        y = 12;
        x = 7;
    }
    if (x < 12 && y < 7)
    {
        x = 12;
        y = 7;
    }

    // Don't go off the left side of the board
    if (x > 66)
    {
        x = 66;
    }

    // Don't go off the bottom of the board
    if (y > 85)
    {
        y = 85;
    }

    // Don't go off the right side of the board
    if (x < -10)
    {
        x = -10;
    }

    // Don't go off the top of the board
    if (y < 0)
    {
        y = 0;
    }

    x = x * 0.82;
    y = y * 0.82;

    // Prevent zero division
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

    // Calculate the wanted servo angles
    double totalLen = sqrt(pow(x, 2) + pow(y, 2));
    double angle2 = acos((-pow(totalLen, 2) + pow(LEN1, 2) + pow(LEN2, 2)) / (2 * LEN1 * LEN2));

    double angle1 = atan(y / x) + acos((pow(LEN1, 2) + pow(x, 2) + pow(y, 2) - pow(LEN2, 2)) / (2 * LEN1 * sqrt(pow(x, 2) + pow(y, 2))));
    double a1 = (angle1 * 180 / PI) + OFFSET1;
    double a2 = (angle2 * 180 / PI) + OFFSET2;

    // Get and set the values associated with the angles
    values[0] = SERVO1.getValue(a1);
    values[1] = SERVO2.getValue(a2);
}