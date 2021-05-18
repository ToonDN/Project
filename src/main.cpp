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
#include "globals.h"

Drawer DRAWER = Drawer();

void ButtonControl()
{
    //* Buttons control
    if (!(PINE & 1 << PINE7)) //* Top
    {
    }
    if (!(PINE & 1 << PINE6)) //* Right
    {
    }
    if (!(PINE & 1 << PINE5)) //* Bottom
    {
    }
    if (!(PINE & 1 << PINE4)) //* Left
    {
    }
    if (!(PINC & 1 << PINC7)) //* Center
    {
    }
}

void InterruptInit()
{
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
    InitAll();

    while (1)
    {
        unsigned char value = UART_Receive();

        if (value == 255)
        {
            unsigned char x = UART_Receive();
            unsigned char y = UART_Receive();

            DRAWER.gotoCoordinates(x / 3.78, y / 3);
        }
        else if (value == 254)
        {
            unsigned char state = UART_Receive();
            DRAWER.Set_Drawstate(state == 1);
        }
    }

    return 0;
}

ISR(TIMER1_COMPA_vect)
{
    //LEDS = TCNT1;
    PORTC = 0xFF;
    PORTD = 0xFF;

    unsigned short v1 = DRAWER.servo1.value;
    unsigned short v2 = DRAWER.servo2.value;
    unsigned short v3 = DRAWER.servoDrawstate.value;

    while (TCNT1 < 5100)
    {
        if (TCNT1 >= v1)
            PORTC &= ~(1 << DRAWER.servo1.pin);

        if (TCNT1 >= v2)
            PORTC &= ~(1 << DRAWER.servo2.pin);

        if (TCNT1 >= v3)
            PORTD &= ~(1 << DRAWER.servoDrawstate.pin);
    }

    DRAWER.rotateTimeLeft -= 1;
    DRAWER.drawNext();
}
