#include "drawer.h"
#include "dwenguino/dwenguino_board.hpp"
#include "dwenguino/dwenguino_lcd.hpp"
#include "figures.h"
#include "servos.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include "bluetooth.h"
#include "shapes.h"
#include "constants.h"

Drawer DRAWER = Drawer();

void InterruptInit()
{
    // Set all register for enabling interrupts
    DDRC = 0xFF;
    DDRD = 0xFF;

    TCCR1A |= 1 << WGM11;
    TCCR1B |= 1 << WGM12 | 1 << WGM13 | 1 << CS11;
    TIMSK1 |= 1 << OCIE1A;

    ICR1 = 39999; //20 ms
    sei();
}

void ServosInit()
{
    DRAWER.servo1.setValue(10000);
    DRAWER.servo2.setValue(10000);
    DRAWER.Set_Drawstate(false);
    _delay_ms(300);
    DRAWER.gotoCoordinates(0, 40);
}

void InitAll()
{
    initBoard();
    LEDS = 0;
    InterruptInit();
    ServosInit();
    UART_Init();
}

int main(void)
{
    // Set all the registers and values
    InitAll();

    while (1)
    {
        unsigned char value = UART_Receive();

        // Receiving coordinates
        if (value == 255)
        {
            unsigned char x = UART_Receive();
            unsigned char y = UART_Receive();

            DRAWER.gotoCoordinates(x / 3.78, y / 3);
        }
        // Receiving drawstate
        else if (value == 254)
        {
            unsigned char state = UART_Receive();
            DRAWER.Set_Drawstate(state == 1);
        } 
        // Receiving shape
        else if (value == 253) {
            
        }
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
