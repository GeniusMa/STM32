/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   spi_flash测试，测试信息通过USART1打印在电脑的超级终端
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
#include "./led/bsp_led.h"
#include "./usart/bsp_usart.h"
#include "./spi/bsp_spi_flash.h"
#include <string.h>

int main(void)
{
	uint32_t id;
	LED_GPIO_Config();
	LED_BLUE;
	USART_Config();
	printf("\r\n 这是一个SPI-FLASH读写程序测试\r\n");
	SPI_FLASH_Init();
	id = SPI_FLASH_ReadID();
	printf("\r\n id=0x%x \r\n",id);
	while(1)
	{
	}
}






/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */

/*********************************************END OF FILE**********************/
