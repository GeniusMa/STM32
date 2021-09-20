#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_systick.h"
#include "usart.h"

int main(void)
{	 
  /* 初始化RGB彩灯 */
  LED_GPIO_Config();
  
  /* 初始化USART 配置模式为 115200 8-N-1 */
  usart_config();
	
  /* 打印指令输入提示信息 */

  while(1)
	{	

  
	}	
}



