#include "drawer.h"
#include "dwenguino/dwenguino_board.hpp"
#include "dwenguino/dwenguino_lcd.hpp"
#include "figures.h"
#include "servos.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <bluetooth_tests.h>
#include "shapes.h"
#include "constants.h"
#include "globals.h"

DwenguinoLCD lcd;

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

void Init()
{
    initBoard();
    LEDS = 0;
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
    DRAWER.Set_Drawstate(false);
    DRAWER.gotoCoordinates(50, 50);
    DRAWER.queue.setPos(50, 50);


    // DRAWER.servoDrawstate.setAngle(175);
    // DRAWER.enqueueShape(&Goto(10, 10));
    // // DRAWER.gotoCoordinates(x, y);

    // _delay_ms(1000);
}

int main(void)
{

    Init();
    ServosInit();

    DRAWER.enqueueShape(&DrawState(true));
    DRAWER.enqueueShape(&Line(30, 70));
    DRAWER.enqueueShape(&Line(80, 50));
    // DRAWER.enqueueShape(&Line(10, 10));
    //DRAWER.enqueueShape(&Goto(1, 5));

    while (1)
    {
        ButtonControl();
    }

    return 0;
}

ISR(TIMER1_COMPA_vect)
{
    //LEDS = TCNT1;
    PORTC = 0xFF;
    PORTD = 0xFF;

    unsigned short v1 = DRAWER.servo1.value;
    unsigned short v2 = DRAWER.servo1.value;
    unsigned short v3 = DRAWER.servoDrawstate.value;

    // unsigned short values[3] = {v1, v2, v3};

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
