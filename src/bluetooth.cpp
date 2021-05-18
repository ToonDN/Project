#include <avr/io.h>
#include <util/delay.h>
#include "dwenguino/dwenguino_board.hpp"
#include "drawer.h"

#define BAUD 9600
#define BRC ((F_CPU / 16 / BAUD) - 1)

unsigned char UART_Receive()
{
    while (!(UCSR1A & (1 << RXC1)))
        ;
    return UDR1;
}

void UART_Send(unsigned char value)
{
}

void UART_Init()
{
    // Set BAUD rate
    UBRR1H = (BRC >> 8);
    UBRR1L = BRC;

    // Enable receiver and transmitter
    UCSR1B = (1 << RXEN1) | (1 << TXEN1);

    // Set the character size to 8 bits
    UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);
}

