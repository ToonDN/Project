#ifndef SERVO_H
#define SERVO_H

class Servo
{

public:
    unsigned short low;
    unsigned short high;
    unsigned char pin;
    unsigned short value = 3000;

    Servo(unsigned short _low, unsigned short _high, unsigned char _pin) : low(_low), high(_high), pin(_pin) {}

    void setAngle(double angle);
    void setValue(unsigned short _value);
    unsigned short getValue(double angle);
};

#endif
