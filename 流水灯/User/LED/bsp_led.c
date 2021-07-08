#include "bsp_led.h"

void LED_GPIO_Comfig(void)
{
	//����һ��GPIO_InitTypeDef��ing�Ľṹ��
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//��ʱ��
	RCC_APB2PeriphClockCmd( LED1_GPIO_CLK | LED2_GPIO_CLK | LED3_GPIO_CLK, ENABLE);
	
	//��ʼ��GPIO
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

