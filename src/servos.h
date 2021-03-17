#ifndef SERVO_H
#define SERVO_H

class Servo
{

public:
    unsigned int low;
    unsigned int high;
    int pin;
    double value;
    double angle = 0;
    bool isRotating = false;

    void rotateTo(double value);
    void setValue();

};

#endif