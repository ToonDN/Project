#include "servos.h"

void Servo::setValue(unsigned short _value)
{
    value = _value;
}

void Servo::setAngle(double angle)
{
    value = low + ((angle / 180) * (high - low));
}

unsigned short Servo::getValue(double angle)
{
    return low + ((angle / 180) * (high - low));
}
