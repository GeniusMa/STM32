#include "bsp_systick.h"


#if 0
static __INLINE uint32_t SysTick_Config(uint32_t ticks)
{ 
  if (ticks > SysTick_LOAD_RELOAD_Msk)  return (1);            //判断 tick值是否大于2^24，如果大于 不符合规则
                                                               
  SysTick->LOAD  = (ticks & SysTick_LOAD_RELOAD_Msk) - 1;      //初始化reload寄存器的值
  NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);  //配置中断优先级为15，默认为最低优先级
  SysTick->VAL   = 0;                                          //初始化counter的值为0
  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |                //配置是systick的时钟为72M
                   SysTick_CTRL_TICKINT_Msk   |                //使能中断  
                   SysTick_CTRL_ENABLE_Msk;                    //使能systick
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

