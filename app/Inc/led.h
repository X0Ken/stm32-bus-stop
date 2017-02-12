#ifndef __LED_H_
#define __LED_H_

#include <stm32f10x_gpio.h>
#define RCC_LED 	RCC_APB2Periph_GPIOB
#define GPIO_LED 	GPIOB

#define PIN_LED 	(GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12\
|GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15)

#define PIN_LED1 	GPIO_Pin_15


void LED_Init(void);

void LED_Sets(uint8_t data);

#define LED1(a) if(a)\
GPIO_WriteBit(GPIO_LED, PIN_LED1, Bit_SET);\
else GPIO_WriteBit(GPIO_LED, PIN_LED1, Bit_RESET);

#endif
