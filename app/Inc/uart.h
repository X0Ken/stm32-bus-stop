#ifndef __UART_H_
#define __UART_H_

#include "stdint.h"

void UART2_GPIO_Configuration(void);
void USART2_Configuration(void);
void UART2SendByte(uint8_t ch);
char UART2GetByte();
void UART2SendString(char *DAT,uint8_t len);

#endif
