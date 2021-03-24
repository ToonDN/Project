#include "servos.h"
#include "drawer.h"
#include "math.h"
#include "queue.h"
#include "node.h"

#include "dwenguino/dwenguino_board.hpp"

const double PI = 3.141592653589793238;
const double ZERO = 0.000000000001;

void Drawer::straightLineTo(double x, double y) {
    queue.add(x, y);
}

void Drawer::goTo(Servo &servo1, Servo &servo2, double x, double y)
{
    if (x == 0)
    {
        x = ZERO;
        y -= ZERO;
    }
    if (y == 0)
    {
        y = ZERO;
        x -= ZERO;
    }

    double totalLen = sqrt(pow(x, 2) + pow(y, 2));
    double angle2 = acos((-pow(totalLen, 2) + pow(len1, 2) + pow(len2, 2)) / (2 * len1 * len2));

    double angle1 = atan(y / x) + acos((pow(len1, 2) + pow(x, 2) + pow(y, 2) - pow(len2, 2)) / (2 * len1 * sqrt(pow(x, 2) + pow(y, 2))));
    double a1 = 180 - (angle1 * 180 / PI) + offset1;
    double a2 = 180 - (angle2 * 180 / PI) + offset2;

    servo1.rotateTo(a1);
    servo2.rotateTo(a2);
}

void Drawer::drawNext(Servo &servo1, Servo &servo2)
{   
    if (rotateTimeLeft <= 0 && not queue.isEmpty())
    {   
        rotateTimeLeft = 100;

        Node node = queue.getFirst();
        double pos1 = node.pos1;
        double pos2 = node.pos2;


        servo1.rotateTo(90);
        servo2.rotateTo(90);

        // Drawer::goTo(servo1, servo2, pos1, pos2);

        queue.remove();
    } else {
        
    }
}
