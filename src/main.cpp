#include "drawer.h"
#include "dwenguino/dwenguino_board.hpp"

#include "servos.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include "shapes.h"
#include "constants.h"
#include "bluetooth.h"
#include "initialization.h"

Drawer DRAWER = Drawer();

int main(void)
{
    // Set all the registers and values
    InitAll(&DRAWER);
    DRAWER.gotoCoordinates(0, 85);

    while (1)
    {
        Receival_Handler(&DRAWER);
    }

    return 0;
}

ISR(TIMER1_COMPA_vect)
{
    // Enable writing to the ports
    PORTC = 0xFF;
    PORTD = 0xFF;

    // Give signal to the servos if their value is reached
    while (TCNT1 < 5100)
    {
        if (TCNT1 >= DRAWER.servo1.value)
            PORTC &= ~(1 << DRAWER.servo1.pin);

        if (TCNT1 >= DRAWER.servo2.value)
            PORTC &= ~(1 << DRAWER.servo2.pin);

        if (TCNT1 >= DRAWER.servoDrawstate.value)
            PORTD &= ~(1 << DRAWER.servoDrawstate.pin);
    }

    // Draw the next item, this is done in the interrupt because the queue is blocking the mainloop
    DRAWER.rotateTimeLeft -= 1;
    DRAWER.drawNext();
}
