#ifndef SERVO_H
#define SERVO_H

class Servo
{

public:
    unsigned short deg_0;
    unsigned short deg_180;
    unsigned short deg_90;
    unsigned char pin;
    unsigned short value = 3000;

    Servo(unsigned short _deg_0, unsigned short _deg_90, unsigned short _deg_180, unsigned char _pin) : deg_0(_deg_0), deg_180(_deg_180), deg_90(_deg_90), pin(_pin) {}

    void setAngle(double angle);
    void setValue(unsigned short _value);
    unsigned short getValue(double angle);
};

#endif
