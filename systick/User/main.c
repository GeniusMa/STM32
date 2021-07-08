/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ����led
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
#include "bsp_led.h"
#include "bsp_systick.h"

#define SOFT_DELAY Delay(0x0FFFFF);

void Delay(__IO u32 nCount); 

/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
int main(void)
{	
	/* LED �˿ڳ�ʼ�� */
	LED_GPIO_Config();	 

	while (1)
	{
		LED1_ON;			  // ��
		//SOFT_DELAY;
		SysTick_Delay_ms(500);
		LED1_OFF;		   // ��

		LED2_ON;			 // ��
		//SOFT_DELAY;
		SysTick_Delay_ms(500);
		LED2_OFF;		   // ��

		LED3_ON;			 // ��
		//SOFT_DELAY;
		SysTick_Delay_ms(500);
		LED3_OFF;		   // ��	 

		/*������ʾ ������������� ��ɫ*/
		LED_RED;
		//SOFT_DELAY;
		SysTick_Delay_ms(500);
		
		LED_GREEN;
		//SOFT_DELAY;
		SysTick_Delay_ms(500);
		
		LED_BLUE;
		//SOFT_DELAY;
		SysTick_Delay_ms(500);
		
		LED_YELLOW;
		//SOFT_DELAY;
		SysTick_Delay_ms(500);
		
		LED_PURPLE;
		//SOFT_DELAY;
		SysTick_Delay_ms(500);
				
		LED_CYAN;
		//SOFT_DELAY;
		SysTick_Delay_ms(500);
		
		LED_WHITE;
		//SOFT_DELAY;
		SysTick_Delay_ms(500);
		
		LED_RGBOFF;
		//SOFT_DELAY;
		SysTick_Delay_ms(500);
			
	}
}

void Delay(__IO uint32_t nCount)	 //�򵥵���ʱ����
{
	for(; nCount != 0; nCount--);
}
/*********************************************END OF FILE**********************/

