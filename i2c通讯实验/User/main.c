/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   �����жϽ��ղ���
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
#include "bsp_usart.h"
#include "bsp_i2c.h"
/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
  
  
uint8_t readData[10] ={0};
uint8_t writeData[8] ={4,5,6,7,8,9,10,11};
  
int main(void)
{	
  uint8_t i=0;
	/*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/
  USART_Config();
	
	/* ����һ���ַ��� */
	printf("����һ��IICͨѶʵ��\n");
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
