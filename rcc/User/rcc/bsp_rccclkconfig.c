#include "bsp_rccclkconfig.h"

void HSE_SetSysClk(uint32_t RCC_PLLMul_x)
{
	ErrorStatus HSEStatus;
	//把RCC 寄存器复位成复位值
	RCC_DeInit();
	//eanable hse
	RCC_HSEConfig(RCC_HSE_ON);
	
	HSEStatus = RCC_WaitForHSEStartUp();
	
	if(HSEStatus == SUCCESS)
	{
		//使能预取指
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		//两个等待 
		FLASH_SetLatency(FLASH_Latency_2);
		//配置分频
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
        RCC_PCLK1Config(RCC_HCLK_Div2);
		RCC_PCLK2Config(RCC_HCLK_Div1);
		//配置锁相环PLLCLK=HSE*RCC_PLLMul_x
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_x);
		//ENABLE PLL
		RCC_PLLCmd(ENABLE);
		//等待PLL稳定
		while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
		//选择系统时钟
		RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE);
		while ( RCC_GetSYSCLKSource() != 0x08 );
	}
	else
	{
		//HSE启动失败添加代码
	}
}


