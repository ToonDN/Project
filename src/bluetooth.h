#include "drawer.h"

#ifndef BLUETOOTH_H
#define BLUETOOTH_H

void UART_Init();

unsigned char UART_Receive();

void UART_Send(unsigned char value);

void Reveival_Handler(Drawer* drawer);

#endif