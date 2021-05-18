#include "servos.h"

void Servo::setValue(unsigned short _value)
{
    value = _value;
}

void Servo::setAngle(double angle)
{
    value = getValue(angle);
}

unsigned short Servo::getValue(double angle)
{
    if (angle > 90)
    {
        return deg_90 + (angle - 90) * ((double(deg_180) - double(deg_90)) / 90);
    }
    else
    {
        return deg_90 - (90 - angle) * ((double(deg_90) - double(deg_0)) / 90);
    }
}
