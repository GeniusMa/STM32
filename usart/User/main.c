#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_systick.h"
#include "usart.h"

int main(void)
{	 
  /* ��ʼ��RGB�ʵ� */
  LED_GPIO_Config();
  
  /* ��ʼ��USART ����ģʽΪ 115200 8-N-1 */
  usart_config();
	
  /* ��ӡָ��������ʾ��Ϣ */

  while(1)
	{	

  
	}	
}



