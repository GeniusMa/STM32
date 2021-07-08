
//#if 0

//#include <rge52.h>

//sbit LED  = P0^0

//void main(void)
//{
//	P0 = 0XFE;     // ���߲���  sfr P0   0X80
//	
//	LED = 0;       // λ����
//}

//#endif



#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

#define LED_G_GPIO_PROT                    GPIOB
#define LED_G_CLK_ENABLE                   (RCC->APB2ENR |= ((1)<<3))
#define LED_G_GPIO_PIN                      GPIO_Pin_1

void Delay(uint32_t count)
{
	for(; count !=0;count--);
}


int main (void)
{
#if 0	
	// �� GPIOB �˿ڵ�ʱ��
	*( unsigned int * )0x40021018 |=  ( (1) << 3 );
	
	// ����IO��Ϊ���
	*( unsigned int * )0x40010C00 &=  ~( (0x0f) << (4*0) );
	*( unsigned int * )0x40010C00 |=  ( (1) << (4*0) );
	
	// ���� ODR �Ĵ���
	*( unsigned int * )0x40010C0C &= ~(1<<0);
	
#elif 0
	
	// �� GPIOB �˿ڵ�ʱ��
	RCC_APB2ENR  |=  ( (1) << 3 );
	
	// ����IO��Ϊ���
	GPIOB_CRL &=  ~( (0x0f) << (4*0) );
	GPIOB_CRL |=  ( (1) << (4*0) );
	
	// ���� ODR �Ĵ���
	GPIOB_ODR &= ~(1<<0);
	//GPIOB_ODR |= (1<<0);

#elif 0
		// �� GPIOB �˿ڵ�ʱ��
	RCC->APB2ENR  |=  ( (1) << 3 );
	
	// ����IO��Ϊ���
	GPIOB->CRL &=  ~( (0x0f) << (4*0) );
	GPIOB->CRL |=  ( (1) << (4*0) );
	
	// ���� ODR �Ĵ���
	GPIOB->ODR &= ~(1<<0);
	//GPIOB->ODR |= (1<<0);
	
	
#elif 0
		// �� GPIOB �˿ڵ�ʱ��
	RCC->APB2ENR  |=  ( (1) << 3 );
	
	// ����IO��Ϊ���
	GPIOB->CRL &=  ~( (0x0f) << (4*0) );
	GPIOB->CRL |=  ( (1) << (4*0) );
	
	GPIO_SetBits    (GPIOB,GPIO_Pin_0);
	GPIO_ResetBits  (GPIOB,GPIO_Pin_0);

#elif 1

	GPIO_InitTypeDef  GPIO_InitStructure;
	
	// �� GPIOB �˿ڵ�ʱ��
	LED_G_CLK_ENABLE;
	
	GPIO_InitStructure.GPIO_Pin = LED_G_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHZ;
	GPIO_Init(LED_G_GPIO_PROT   , &GPIO_InitStructure);	

	while(1)
	{
		GPIO_SetBits(LED_G_GPIO_PROT   ,LED_G_GPIO_PIN);  
        Delay(0xFFFF);
		GPIO_ResetBits( LED_G_GPIO_PROT   ,LED_G_GPIO_PIN );
		Delay(0xFFFF);
	}
	
#endif
}


void SystemInit(void)
{
	// ������Ϊ�գ�Ŀ����Ϊ��ƭ��������������
}








