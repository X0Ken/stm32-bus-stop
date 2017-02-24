#include "OSConfig.h"
#include "led.h"
#include "uart.h"
#include "gpio.h"
#include "SYN6288.h"
#include <CoOS.h>
#include <stm32f10x.h>

#define TASK_STK_SIZE 128        /*!< Define stack size.                       \
                                    */
OS_STK led_Stk[TASK_STK_SIZE];   /*!< Stack of 'task_init' task.	  */
OS_STK speak_Stk[TASK_STK_SIZE]; /*!< Stack of 'task_init' task.	  */

unsigned char unicstr[100];

char a[] = {0xFD, 0x00, 0x0B, 0x01, 0x00, 0xD3, 0xEE,
            0xD2, 0xF4, 0xCC, 0xEC, 0xCF, 0xC2, 0xC1};

void Delay(uint16_t);
void led_task(void *pdata);
void speak_task(void *pdata);

int main(void) {
  LED_Init();
  LED_Sets(0x00);
  GPIO_Configuration();
  USART2_Configuration();
  CoInitOS();
  CoCreateTask(led_task, (void *)0, 10, &led_Stk[TASK_STK_SIZE - 1],
               TASK_STK_SIZE);
  CoCreateTask(speak_task, (void *)0, 10, &speak_Stk[TASK_STK_SIZE - 1],
               TASK_STK_SIZE);
  CoStartOS();
  while (1)
    ;
}

void led_task(void *pdata) {
  while (1) {
    LED1(1);
    Delay(10);
    LED1(0);
    Delay(10);
  }
}

void speak_task(void *pdata) {
  while (1) {
		UART2SendString(a, 14);
		Delay(10);
		utf8_to_unicode((unsigned char *)"笨蛋", unicstr);
    SYN_FrameInfo(1, (char *)unicstr);
    Delay(10);
  }
}

void Delay(uint16_t c) {
  uint16_t a, b;
  for (; c > 0; c--)
    for (a = 1000; a > 0; a--)
      for (b = 1000; b > 0; b--)
        ;
}
