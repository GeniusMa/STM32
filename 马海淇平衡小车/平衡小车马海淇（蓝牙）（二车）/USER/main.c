#include "stm32f10x.h"
#include "sys.h" 

float Pitch,Roll,Yaw;						
short gyrox,gyroy,gyroz;			
short aacx,aacy,aacz;						
int Encoder_Left,Encoder_Right;	
int PWM_MAX=7200,PWM_MIN=-7200;	
int MOTO1,MOTO2;								
extern int Vertical_out,Velocity_out,Turn_out;
int main(void)	
{
	delay_init();
	NVIC_Config();
	uart1_init(115200);	
	uart3_init(9600); 
	delay_ms(100);
	USART3_Send_String("AT\r\n");
	USART3_Send_String("AT+NAME MHQBlance\r\n");
	delay_ms(100);	
	USART3_Send_String("AT+BAUD8\r\n"); 	
	delay_ms(100);		
	uart3_init(115200);
	OLED_Init();
	OLED_Clear();
	
	MPU_Init();
	mpu_dmp_init();
	MPU6050_EXTI_Init();
	
	Encoder_TIM2_Init();
	Encoder_TIM4_Init();
	Motor_Init();
	PWM_Init_TIM1(0,7199);
  while(1)	
	{
		OLED_Float(0,0,Pitch,1);
		OLED_Float(50,50,Velocity_out,1);
	} 	
}



