#ifndef __BSP_EXTI_H
#define __BSP_EXTI_H

#include "stm32f10x.h" 

#define KEY1_INT_GPIO_PORT    	GPIOA			              /* GPIO端口 */
#define KEY1_INT_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO端口时钟 */
#define KEY1_INT_GPIO_PIN		GPIO_Pin_0			        /* 连接到SCL时钟线的GPIO */

void EXTI_Key_Config(void);
#endif /*__BSP_EXTI_H*/

