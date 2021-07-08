#ifndef __MOTOR_H
#define __MOTOR_H
#include "stm32f10x.h"
#include "sys.h"
#define IN1 PBout(14)
#define IN2 PBout(15)	
#define IN3 PAout(6)
#define IN4 PAout(7)
void PWM_Config(u8 CCR1_Val,u8 CCR1_Va2);
void PWM_GPIO_Config(void);
void PWM_INIT(void);
#endif

