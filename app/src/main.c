#include <CoOS.h>
#include <stm32f10x.h>
#include "led.h"
#include "OSConfig.h"

#define TASK_STK_SIZE		128	 		/*!< Define stack size.				  */
OS_STK   led_Stk[TASK_STK_SIZE];	 	/*!< Stack of 'task_init' task.	  */


void Delay(uint16_t);
void led_task(void *pdata);


int main(void)
{
	LED_Init();
	LED_Sets(0x00);
	CoInitOS();
	CoCreateTask(led_task, (void *)0, 10,&led_Stk[TASK_STK_SIZE-1], TASK_STK_SIZE);
	CoStartOS();
	while (1);
}

void led_task(void *pdata){
	while (1)
	{
		LED1(1);
		Delay(10);
		LED1(0);
		Delay(10);
	}
}

void Delay(uint16_t c)
{
	uint16_t a,b;
	for(; c>0; c--)
		for(a=1000; a>0; a--)
			for(b=1000; b>0; b--);
}
