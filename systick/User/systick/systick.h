#ifndef __SYSTICK_H
#define __SYSTICK_H
#include "stm32f10x.h"
#include "core_cm3.h"


void Systick_Delay_us(uint32_t us);
void Systick_Delay_ms(uint32_t ms);
#endif /*__SYSTICK_H*/

