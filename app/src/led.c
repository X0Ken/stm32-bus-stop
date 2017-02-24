#include <stm32f10x.h>
#include "led.h"


void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = PIN_LED;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

	RCC_APB2PeriphClockCmd(RCC_LED, ENABLE);

	GPIO_Init(GPIO_LED, &GPIO_InitStructure);

}


void LED_Sets(uint8_t data)
{
	uint16_t setValue;

	setValue = GPIO_ReadOutputData(GPIO_LED);
	setValue &= 0x00ff;
	setValue |= (uint16_t)data << 8;

	GPIO_Write(GPIO_LED,setValue);
}
