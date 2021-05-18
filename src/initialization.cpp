#include <avr/interrupt.h>
#include <avr/io.h>
#include "drawer.h"
#include "dwenguino/dwenguino_lcd.hpp"
#include "bluetooth.h"


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

void ServosInit(Drawer* drawer)
{
    drawer->servo1.setValue(10000);
    drawer->servo2.setValue(10000);
    drawer->Set_Drawstate(false);
    _delay_ms(300);
    drawer->gotoCoordinates(0, 40);
}

void InitAll(Drawer* drawer)
{
    initBoard();
    LEDS = 0;
    InterruptInit();
    ServosInit(drawer);
    UART_Init();
}