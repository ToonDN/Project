#include "drawer.h"
#include "dwenguino/dwenguino_board.hpp"
#include "dwenguino/dwenguino_lcd.hpp"
#include "figures.h"
#include "servos.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <bluetooth_tests.h>

DwenguinoLCD lcd;

Drawer drawer = Drawer();


void ButtonControl() {
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

int main(void) {
    initBoard();
    LEDS = 0;

    mainTest();

    
    

    return 5;
    testfigures();

    initBoard();
    LEDS = 0;

    // Create servo variables
    //* Servo 1 heeft het rechte stuk, Servo 2 heeft het ronde stuk

    // Set servos as output
    DDRC = 0xFF;
    DDRD = 0xFF;

    TCCR1A |= 1 << WGM11;
    TCCR1B |= 1 << WGM12 | 1 << WGM13 | 1 << CS11;
    TIMSK1 |= 1 << OCIE1A;

    ICR1 = 39999; //20 ms
    sei();

    lcd.initLCD();
    // drawer.servo1.rotateTo(45);
    // drawer.servo2.rotateTo(45);
    drawer.Set_Drawstate(true);
    ;
    // for (int i = 1; i < 50; i++) {
    //   drawer.enqueue(i, i);
    // }
    // drawer.servo1.rotateTo(90);
    // drawer.servo2.rotateTo(45);
    drawer.enqueue(77.1, 0);

    // drawer.draw_Square(Square())

    while (1) {
        drawer.drawNext();

        ButtonControl();
    }

    return 0;
}

// ISR(TIMER1_COMPA_vect) {
//     // LEDS = TCNT1;
//     PORTC = 0xFF;
//     PORTD = 0xFF;

//     while (TCNT1 < 5100) {
//         if (TCNT1 >= drawer.servo1.value)
//             PORTC &= ~(1 << drawer.servo1.pin);

//         if (TCNT1 >= drawer.servo2.value)
//             PORTC &= ~(1 << drawer.servo2.pin);
//         if (TCNT1 >= drawer.servo_drawstate.value)
//             PORTD &= ~(1 << drawer.servo_drawstate.pin);
//     }

//     drawer.rotateTimeLeft -= 1;
// }


