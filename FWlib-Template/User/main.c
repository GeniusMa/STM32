#include "stm32f10x.h"
#include "bsp_led.h"

void Delay(uint32_t count)
{
	for(;count!=0;count--);
}

int main(void)
{
	//系统时钟被配置为72M
	LED_GPIO_Config();
	
	while(1)
	{
		//GPIO_SetBits(LED_G_GPIO_PORT , LED_G_GPIO_PIN );
		LED_G(OFF);
		Delay(0xFFFFF);
		//GPIO_ResetBits(LED_G_GPIO_PORT, LED_G_GPIO_PIN);
		LED_G(ON);
		Delay(0xFFFFF);
	}
}

