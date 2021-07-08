/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   测试led
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
#include "bsp_led.h"
#include "bsp_usart.h"

/**
  * @brief  主函数
  * @param  无  
  * @retval 无
  */
int main(void)
{	
	//uint8_t a[10] ={1,2,3,4,5,6,7,8,9,10};
	uint8_t ch;
	USART_Config();
	LED_GPIO_Config();
	
	//Usart_SendByte(DEBUG_USARTx ,'L' );
	//Usart_SendHalfWord(DEBUG_USARTx,0xff56 );
	
	//Usart_SendArry(DEBUG_USARTx,a , 10);
	//Usart_SendSTR(DEBUG_USARTx,"耿令波是个大SB \n" );
	
	while (1)
	{
		ch=getchar();
		printf("亮灯=%c\n",ch);
		
		switch(ch)
		{
			case '1':LED_RED;
				break;
			case '2':LED_GREEN;
				break;
			case '3':LED_BLUE;
				break;
			default:LED_RGBOFF
				break;
		}
	}
}


/*********************************************END OF FILE**********************/
