/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   spi_flash���ԣ�������Ϣͨ��USART1��ӡ�ڵ��Եĳ����ն�
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� F103-ָ���� STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
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
	printf("\r\n ����һ��SPI-FLASH��д�������\r\n");
	SPI_FLASH_Init();
	id = SPI_FLASH_ReadID();
	printf("\r\n id=0x%x \r\n",id);
	while(1)
	{
	}
}






/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */

/*********************************************END OF FILE**********************/
