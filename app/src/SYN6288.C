/***************************飞音云电子****************************
**  工程名称：YS-SYN6288语音合成配套程序
**	CPU: STC89LE52
**	晶振：22.1184MHZ
**	波特率：9600 bit/S
**	配套产品信息：YS-SYN6288语音合成模块
**                http://yuesheng001.taobao.com
**  作者：zdings
**  联系：751956552@qq.com
**  修改日期：2012.8.25
**  说明：。。
**************************飞音云电子******************************/
#include "uart.h"
#include <string.h>

/**************芯片设置命令*********************/
uint8_t SYN_StopCom[] = {0xFD, 0X00, 0X02, 0X02, 0XFD};    //停止合成
uint8_t SYN_SuspendCom[] = {0XFD, 0X00, 0X02, 0X03, 0XFC}; //暂停合成
uint8_t SYN_RecoverCom[] = {0XFD, 0X00, 0X02, 0X04, 0XFB}; //恢复合成
uint8_t SYN_ChackCom[] = {0XFD, 0X00, 0X02, 0X21, 0XDE};   //状态查询
uint8_t SYN_PowerDownCom[] = {0XFD, 0X00, 0X02, 0X88,
                              0X77}; //进入POWER DOWN 状态命令

/***********************************************/


/***********************************************************
* 名    称：  YS-SYN6288 文本合成函数
* 功    能：  发送合成文本到SYN6288芯片进行合成播放
* 入口参数：Music(背景音乐选择):0无背景音乐。1-15：相关背景音乐
            *HZdata:文本指针变量
* 出口参数：
* 说    明： 本函数只用于文本合成，具备背景音乐选择。默认波特率9600bps。
* 调用方法：例： SYN_FrameInfo（0，“乐声电子科技”）；
**********************************************************/
void SYN_FrameInfo(char Music, char *HZdata) {
  /****************需要发送的文本**********************************/
  char Frame_Info[50];
  char HZ_Length;
  char ecc = 0; //定义校验字节
  int i = 0;
  HZ_Length = strlen(HZdata); //需要发送文本的长度

  /*****************帧固定配置信息**************************************/
  Frame_Info[0] = 0xFD;              //构造帧头FD
  Frame_Info[1] = 0x00;              //构造数据区长度的高字节
  Frame_Info[2] = HZ_Length + 3;     //构造数据区长度的低字节
  Frame_Info[3] = 0x01;              //构造命令字：合成播放命令
  Frame_Info[4] = 0x03 | Music << 3; //构造命令参数：背景音乐设定

  /*******************校验码计算***************************************/
  for (i = 0; i < 5; i++) //依次发送构造好的5个帧头字节
  {
    ecc = ecc ^ (Frame_Info[i]); //对发送的字节进行异或校验
  }

  for (i = 0; i < HZ_Length; i++) //依次发送待合成的文本数据
  {
    ecc = ecc ^ (HZdata[i]); //对发送的字节进行异或校验
  }
  /*******************发送帧信息***************************************/
  memcpy(&Frame_Info[5], HZdata, HZ_Length);
  Frame_Info[5 + HZ_Length] = ecc;
  UART2SendString(Frame_Info, 5 + HZ_Length + 1);
}

/***********************************************************
* 名    称： void  main(void)
* 功    能： 主函数	程序入口
* 入口参数： *Info_data:固定的配置信息变量
* 出口参数：
* 说    明：本函数用于配置，停止合成、暂停合成等设置 ，默认波特率9600bps。
* 调用方法：通过调用已经定义的相关数组进行配置。
**********************************************************/
void YS_SYN_Set(char *Info_data) {
  char Com_Len;
  Com_Len = strlen(Info_data);
  UART2SendString(Info_data, Com_Len);
}

int utf8_to_unicode(unsigned char *pUTF8, unsigned char *pUNIC) {
  // SYN6288中unicode编码采用大端模式
  // b1 表示UTF-8编码的pInput中的高字节, b2  表示次高字节, ...
  unsigned char b1, b2, b3, b4;
  int utfbytes = 0;
  while (*pUTF8 != '\0') {
    b1 = *pUTF8;
    if ((b1 & 0x80) == 0x0) // utf8 - one byte
    {
      utfbytes = utfbytes + 2;
      *pUNIC = 0x00;
      *(pUNIC + 1) = b1;
      pUTF8++;
      pUNIC = pUNIC + 2;
    }
		else if ((b1 & 0xE0) == 0xC0) // utf8 - two byte
    {
      utfbytes = utfbytes + 2;
      b1 = *pUTF8;
      b2 = *(pUTF8 + 1);
      if ((b2 & 0xC0) != 0x80)
        return 0;
      *pUNIC = (b1 >> 2) & 0x07;
      *(pUNIC + 1) = (b1 << 6) + (b2 & 0x3F);
      pUTF8 = pUTF8 + 2;
      pUNIC = pUNIC + 2;
    }
		else if ((b1 & 0xF0) == 0xE0) // utf8 - three byte
    {
      utfbytes = utfbytes + 2;
      b1 = *pUTF8;
      b2 = *(pUTF8 + 1);
      b3 = *(pUTF8 + 2);
      if (((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80))
        return 0;
      *pUNIC = (b1 << 4) + ((b2 >> 2) & 0x0F);
      *(pUNIC + 1) = (b2 << 6) + (b3 & 0x3F);
      pUTF8 = pUTF8 + 3;
      pUNIC = pUNIC + 2;
    } else if ((b1 & 0xF8) == 0xF0) // utf8 - four byte
    {
      utfbytes = utfbytes + 3;
      b1 = *pUTF8;
      b2 = *(pUTF8 + 1);
      b3 = *(pUTF8 + 2);
      b4 = *(pUTF8 + 3);
      if (((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80) ||
          ((b4 & 0xC0) != 0x80))
        return 0;
      *pUNIC = ((b1 << 2) & 0x1C) + ((b2 >> 4) & 0x03);
      *(pUNIC + 1) = (b2 << 4) + ((b3 >> 2) & 0x0F);
      *(pUNIC + 2) = (b3 << 6) + (b4 & 0x3F);
      pUTF8 = pUTF8 + 4;
      pUNIC = pUNIC + 3;
    }
  }
  *pUNIC = '\0';
  return utfbytes;
}
