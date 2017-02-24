#include <stm32f10x.h>

void GPIO_Configuration(void) {
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
