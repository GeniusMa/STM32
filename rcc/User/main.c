#include "stm32f10x.h"
#include "bsp_rccclkconfig.h"

int main (void)
{
	HSE_SetSysClk(RCC_PLLMul_16);
}

