#include "drawer.h"

#ifndef BLUETOOTH_H
#define BLUETOOTH_H
/**
 * @brief initiate bluetooth communication
 * 
 */
void UART_Init();
/**
 * @brief recieve unsigned char via bluetooth
 * 
 * @return unsigned char 
 */
unsigned char UART_Receive();

/**
 * @brief listen for instructions
 * 
 * @param drawer 
 */
void Receival_Handler(Drawer* drawer);

#endif