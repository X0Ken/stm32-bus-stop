#include "uart.h"
#include "stm32f10x_usart.h"

void UART2_GPIO_Configuration(void) {
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB1Periph_USART2 |
                             RCC_APB2Periph_GPIOB,
                         ENABLE); //这里如果没有 RCC_APB2Periph_GPIOA 就没输出
  //          RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART2, ENABLE  );
  /* Configure USART2 Tx (PA.02) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;         //        选中管脚2
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   // 复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; // 最高输出速率50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);            // 选择A端口

  /* Configure USART2 Rx (PA.03) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;             //选中管脚3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);                //选择A端口

  // /*I2C I/O口配置 PB6，PB7 */
  // GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6;
  // GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  // GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  // GPIO_Init(GPIOB, &GPIO_InitStructure);
  //
  // GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7;
  // GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  // GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  // GPIO_Init(GPIOB, &GPIO_InitStructure);
  //
  // /*按键输入 I/O口配置 PB14 */
  // GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9;
  // GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  // GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  // GPIO_Init(GPIOB, &GPIO_InitStructure);
  //
  //          /* Configure LED (PB.8) as PP OUT */
  // GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //选中管脚8
  // GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;          //推拉输出
  // GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;                 //
  // 最高输出速率2MHz
  // GPIO_Init(GPIOB, &GPIO_InitStructure); //选择B端口
}

void USART2_Configuration(void) {
  USART_InitTypeDef USART_InitStructure;
  USART_ClockInitTypeDef USART_ClockInitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); // RCC_APB1Periph_TIM2
                                                         // |

  USART_ClockInitStructure.USART_Clock = USART_Clock_Disable; // 时钟低电平活动
  USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;       // 时钟低电平
  USART_ClockInitStructure.USART_CPHA =
      USART_CPHA_2Edge; // 时钟第二个边沿进行数据捕获
  USART_ClockInitStructure.USART_LastBit =
      USART_LastBit_Disable; // 最后一位数据的时钟脉冲不从SCLK输出
  /* Configure the USART2 synchronous paramters */
  USART_ClockInit(USART2, &USART_ClockInitStructure); // 时钟参数初始化设置

  USART_InitStructure.USART_BaudRate = 9600; // 波特率为：9600
  USART_InitStructure.USART_WordLength = USART_WordLength_8b; // 8位数据
  USART_InitStructure.USART_StopBits =
      USART_StopBits_1; // 在帧结尾传输1个停止位
  USART_InitStructure.USART_Parity = USART_Parity_No; // 奇偶失能
  USART_InitStructure.USART_HardwareFlowControl =
      USART_HardwareFlowControl_None; // 硬件流控制失能

  USART_InitStructure.USART_Mode =
      USART_Mode_Rx | USART_Mode_Tx; // 发送使能+接收使能
  /* Configure USART2 basic and asynchronous paramters */
  USART_Init(USART2, &USART_InitStructure);

  /* Enable USART2 */
  USART_ClearFlag(USART2, USART_IT_RXNE); //清中断，以免一启用中断后立即产生中断
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); //使能USART2中断源
  USART_Cmd(USART2, ENABLE);                     // USART2总开关：开启
}

void UART2SendByte(uint8_t ch) {
  /* 发送一个字节数据到USART2 */
  USART_SendData(USART2, (uint8_t)ch);

  /* 等待发送完毕 */
  while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET)
    ;
}

/// 重定向c库函数scanf到USART2
char UART2GetByte() {
  /* 等待串口1输入数据 */
  while (USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET)
    ;

  return (char)USART_ReceiveData(USART2);
}

/************************************************************************
功能描述： 串口发送字符串数据
入口参数： 	*DAT：字符串指针
返 回 值： none
其他说明： API 供外部使用，直观！
**************************************************************************/
void UART2SendString(char *data,uint8_t len)
{
	for(uint8_t i=0;i<len;i++)
	{
	 	UART2SendByte(data[i]);
	}
}
