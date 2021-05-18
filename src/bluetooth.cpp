#include <avr/io.h>
#include <util/delay.h>
#include "dwenguino/dwenguino_board.hpp"
#include "drawer.h"

#define BAUD 9600
#define BRC ((F_CPU / 16 / BAUD) - 1)

unsigned char UART_Receive()
{
    // Wait for the transfer to finish
    while (!(UCSR1A & (1 << RXC1)))
        ;

    // Return the received value
    return UDR1;
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

void Receival_Handler(Drawer *drawer)
{
    unsigned char value = UART_Receive();

    // Receiving coordinates
    if (value == 255)
    {
        unsigned char x = UART_Receive();
        unsigned char y = UART_Receive();

        drawer->gotoCoordinates(x / 3.78, y / 3);
    }
    // Receiving drawstate
    else if (value == 254)
    {
        unsigned char state = UART_Receive();
        drawer->Set_Drawstate(state == 1);
    }
    // Receiving shape
    else if (value == 253)
    {
        unsigned char shape = UART_Receive();

        // Line
        if (shape == 255)
        {
        }
        // Square
        else if (shape == 254)
        {
        }
        // Bezier curve
        else if (shape == 253)
        {
        }
        // Circle
        else if (shape == 252)
        {
        }
        // Smiley
        else if (shape == 251)
        {
        }
    }
}
