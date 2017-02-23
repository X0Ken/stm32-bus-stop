#ifndef __SPEAK_H_
#define __SPEAK_H_

#include "stm32f10x.h"
#include <stdio.h>

void UART2_GPIO_Configuration(void);
void USART2_Configuration(void);
int fputc(int ch, FILE *f);
int fgetc(FILE *f);

#endif
