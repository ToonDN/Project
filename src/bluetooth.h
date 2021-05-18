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
 * @brief send unsigned char via bluetooth 
 * 
 * @param value 
 */
void UART_Send(unsigned char value);
/**
 * @brief listen for instructions
 * 
 * @param drawer 
 */
void Receival_Handler(Drawer* drawer);

#endif