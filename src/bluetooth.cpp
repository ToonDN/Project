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
        drawer->setDrawstate(state == 1);
    }
    // Receiving shape
    else if (value == 253)
    {
        unsigned char shape = UART_Receive();

        // Line
        if (shape == 255)
        {
            unsigned char x = UART_Receive();
            unsigned char y = UART_Receive();
            drawer->enqueueShape(&Line(x, y));
        }
        // Square
        else if (shape == 254)
        {
            unsigned char p0_x = UART_Receive();
            unsigned char p0_y = UART_Receive();
            unsigned char p1_x = UART_Receive();
            unsigned char p1_y = UART_Receive();
            drawer->enqueueShape(&Square(p0_x, p0_y, p1_x, p1_y));
        }
        // Bezier curve
        else if (shape == 253)
        {
            unsigned char p0_x = UART_Receive();
            unsigned char p0_y = UART_Receive();
            unsigned char p1_x = UART_Receive();
            unsigned char p1_y = UART_Receive();
            unsigned char p2_x = UART_Receive();
            unsigned char p2_y = UART_Receive();
            drawer->enqueueShape(&Bezier(p0_x, p0_y, p1_x, p1_y, p2_x, p2_y));
        }
        // Circle
        else if (shape == 252)
        {
            unsigned char x = UART_Receive();
            unsigned char y = UART_Receive();
            unsigned char r = UART_Receive();
            drawer->enqueueShape(&Circle(x, y, r));
        }
        // Smiley
        else if (shape == 251)
        {
            drawer->enqueueShape(&Smiley());
        }

        // Goto
        else if (shape == 250)
        {
            unsigned char x = UART_Receive();
            unsigned char y = UART_Receive();
            drawer->enqueueShape(&Goto(x, y));
        }

        // Drawstate
        else if (shape == 249)
        {
            unsigned char state = UART_Receive();
            drawer->enqueueShape(&DrawState(state));
        }
        // Start-end line
        else if (shape == 248) {
            unsigned char x1 = UART_Receive();
            unsigned char y1 = UART_Receive();
            unsigned char x2 = UART_Receive();
            unsigned char y2 = UART_Receive();
            drawer->enqueueShape(&DrawState(false));
            drawer->enqueueShape(&Goto(x1, y1));
            drawer->enqueueShape(&DrawState(true));
            drawer->enqueueShape(&Line(x2, y2));
            drawer->enqueueShape(&Line(x2, y2));
            drawer->enqueueShape(&DrawState(false));

        }
    }
}
