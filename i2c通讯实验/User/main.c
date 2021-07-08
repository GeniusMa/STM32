/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   串口中断接收测试
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 F103-指南者 STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
 
 
#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_i2c.h"
/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
  
  
uint8_t readData[10] ={0};
uint8_t writeData[8] ={4,5,6,7,8,9,10,11};
  
int main(void)
{	
  uint8_t i=0;
	/*初始化USART 配置模式为 115200 8-N-1，中断接收*/
  USART_Config();
	
	/* 发送一个字符串 */
	printf("这是一个IIC通讯实验\n");
	I2C_EE_Config();
	
	EEPROM_Byte_Write(11,0x55);
	EEPROM_WaitForWritrEnd();
	
	EEPROM_Byte_Write(12,0x52);
	EEPROM_WaitForWritrEnd();
	
	
	
	EEPROM_Read(11,readData,2);
	
	
	printf("0x%x 0x%x ",readData[0],readData[1]);
	
  while(1)
	{	
		
	}	
}
/*********************************************END OF FILE**********************/
