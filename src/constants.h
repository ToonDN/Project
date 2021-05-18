#include "servos.h"
#include "dwenguino/dwenguino_board.hpp"

#ifndef CONSTANTS_H
#define CONSTANTS_H

#define PI 3.141592653589793238
#define ZERO 0.000000000001

#define LEN1 12.7 / 0.277
#define LEN2 14.8 / 0.277

#define OFFSET1 0
#define OFFSET2 0

#define SERVO1  Servo(5040, 3100, 1430, PINC0)
#define SERVO2  Servo(4705, 2875, 1110, PINC1)
#define SERVO_DRAWSTATE  Servo(1330, 3100, 4750, PIND7)

#endif