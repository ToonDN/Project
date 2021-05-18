#include "servos.h"
#include "dwenguino/dwenguino_board.hpp"

#ifndef CONSTANTS_H
#define CONSTANTS_H

#define PI 3.141592653589793238
#define ZERO 0.000000000001
/**
 * @brief length of the arms
 * 
 */
#define LEN1 12.7 / 0.277
#define LEN2 14.8 / 0.277

/**
 * @brief the servo constructors
 * 
 */
#define SERVO1  Servo(5040, 3100, 1430, PINC0)
#define SERVO2  Servo(4705, 2875, 1110, PINC1)
#define SERVO_DRAWSTATE  Servo(1330, 3100, 4750, PIND7)

/**
 * @brief maximum allowed length of the queue
 * 
 */
#define MAX_QUEUE_LENGTH 200

#endif