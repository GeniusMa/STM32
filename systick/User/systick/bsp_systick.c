#include "bsp_systick.h"


#if 0
static __INLINE uint32_t SysTick_Config(uint32_t ticks)
{ 
  if (ticks > SysTick_LOAD_RELOAD_Msk)  return (1);            //�ж� tickֵ�Ƿ����2^24��������� �����Ϲ���
                                                               
  SysTick->LOAD  = (ticks & SysTick_LOAD_RELOAD_Msk) - 1;      //��ʼ��reload�Ĵ�����ֵ
  NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);  //�����ж����ȼ�Ϊ15��Ĭ��Ϊ������ȼ�
  SysTick->VAL   = 0;                                          //��ʼ��counter��ֵΪ0
  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |                //������systick��ʱ��Ϊ72M
                   SysTick_CTRL_TICKINT_Msk   |                //ʹ���ж�  
                   SysTick_CTRL_ENABLE_Msk;                    //ʹ��systick
  return (0);                                                  
}
#endif

void SysTick_Delay_us(uint32_t us)
{
	uint32_t i;
	SysTick_Config(72);
	
	for(i=0;i<us;i++)
	{
		while(!((SysTick->CTRL)&(1<<16)));
	}

	SysTick->CTRL &=~ SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Delay_ms(uint32_t ms)
{
	uint32_t i;
	SysTick_Config(72000);
	
	for(i=0;i<ms;i++)
	{
		while(!((SysTick->CTRL)&(1<<16)));
	}

	SysTick->CTRL &=~ SysTick_CTRL_ENABLE_Msk;
}

