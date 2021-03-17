#include "servos.h"


void Servo::rotateTo(double value)
{
    angle = value;
    setValue();
}

void Servo::setValue()
{
    value = low + ((angle / 180) * (high - low));
}

