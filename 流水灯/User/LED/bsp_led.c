#include "bsp_led.h"

void LED_GPIO_Comfig(void)
{
	//定义一个GPIO_InitTypeDef类ing的结构体
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//打开时钟
	RCC_APB2PeriphClockCmd( LED1_GPIO_CLK | LED2_GPIO_CLK | LED3_GPIO_CLK, ENABLE);
	
	//初始化GPIO
	GPIO_InitStructure.GPIO_Pin   =LED1_GPIO_PIN ;
	GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  =GPIO_Mode_Out_PP;
	GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);
	
	//
	GPIO_InitStructure.GPIO_Pin   =LED2_GPIO_PIN ;
	GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  =GPIO_Mode_Out_PP;
	GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStructure);
	
	//
	GPIO_InitStructure.GPIO_Pin   =LED3_GPIO_PIN ;
	GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  =GPIO_Mode_Out_PP;
	GPIO_Init(LED3_GPIO_PORT, &GPIO_InitStructure);
	
}

