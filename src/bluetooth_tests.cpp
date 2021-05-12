#include <avr/io.h>
#include <util/delay.h>
#include "dwenguino/dwenguino_board.hpp"

#define BAUD    9600
#define BRC     ((F_CPU/16/BAUD) - 1)


void mainTest() {
    UBRR1H = (BRC >> 8);
    UBRR1L = BRC;

    UCSR1B = (1 << TXEN1);

    UCSR1C = (1 << UCSZ11) | (1 << UCSZ10); // Set the character size to 8 bits

    while(1)
    {
        UDR1 = '8';
        _delay_ms(1000);
    }
}