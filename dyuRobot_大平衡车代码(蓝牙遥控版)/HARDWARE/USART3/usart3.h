#ifndef __USRAT3_H
#define __USRAT3_H 
#include "sys.h"	  	
/**************************************************************************
 作  者 ：大鱼电子
 淘宝地址：https://shop119207236.taobao.com
 微信公众号【大鱼机器人】
 后台回复【平衡小车】：获取平衡小车全套DIY资料
 后台回复【电子开发工具】：获取电子工程师必备开发工具
 后台回复【电子设计资料】：获取电子设计资料包
 知乎：张巧龙 
**************************************************************************/
extern u8 Usart3_Receive;
void uart3_init(u32 bound);
void USART3_IRQHandler(void);
void Uart3SendByte(char byte);   //串口发送一个字节
void Uart3SendBuf(char *buf, u16 len);
void Uart3SendStr(char *str);
#endif

