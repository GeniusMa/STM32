#include "stm32f10x.h"
#include "bsp_led.h"
#include "systick.h"
int main()
{
	LED_GPIO_Config();
	while (1)
	{
			LED_RED;
		Systick_Delay_ms(1000);
		LED_RGBOFF;
		Systick_Delay_ms(1000);
		LED_GREEN;
		Systick_Delay_ms(1000);
		LED_RGBOFF;
		Systick_Delay_ms(1000);
		LED_BLUE;
		Systick_Delay_ms(1000);
		LED_RGBOFF;
		Systick_Delay_ms(1000);
		LED_YELLOW;
		Systick_Delay_ms(1000);
		LED_RGBOFF;
		Systick_Delay_ms(1000);
		LED_PURPLE;
		Systick_Delay_ms(1000);
		LED_RGBOFF;
		Systick_Delay_ms(1000);
		LED_CYAN;
		Systick_Delay_ms(1000);
		LED_RGBOFF;
		Systick_Delay_ms(1000);
		LED_WHITE;
		Systick_Delay_ms(1000);
		LED_RGBOFF;
		Systick_Delay_ms(1000);
	}
	return 0;
}

