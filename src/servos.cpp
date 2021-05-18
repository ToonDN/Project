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
    // Interpolate between the 90° and 180° values if value greater 90°
    if (angle > 90)
    {
        return deg_90 + (angle - 90) * ((double(deg_180) - double(deg_90)) / 90);
    }
    // Interpolate between the 0° and 90° values if the value is less than 90°
    else
    {
        return deg_90 - (90 - angle) * ((double(deg_90) - double(deg_0)) / 90);
    }
}
