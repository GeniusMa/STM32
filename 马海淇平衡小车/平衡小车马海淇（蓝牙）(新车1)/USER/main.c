#include "stm32f10x.h"
#include "sys.h" 

float Pitch,Roll,Yaw;						//角度
short gyrox,gyroy,gyroz;				//陀螺仪--角速度
short aacx,aacy,aacz;						//加速度
int Encoder_Left,Encoder_Right;	//编码器数据（速度）

int PWM_MAX=7200,PWM_MIN=-7200;	//PWM限幅变量
int MOTO1,MOTO2;								//电机装载变量

extern int Vertical_out,Velocity_out,Turn_out;
int main(void)	
{
	delay_init();
	NVIC_Config();
	uart1_init(115200);	
	
	//一、//
	/**************************************************/
	uart3_init(115200);
	USART3_Send_String("AT+NAME=MHQBlance \r\n");
	USART3_Send_String("AT+PIN=9999 \r\n");
	USART3_Send_String("AT+ROLE=0 \r\n");
	USART3_Send_String("AT+CMODE=0 \r\n");
	/**********************************************/
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



////二、////若你的蓝牙默认波特率不是115200，则将下面代码直接替换到上面“一”处即可。
//	/*****************若蓝牙默认波特率为9600，则先设置9600，再修改蓝牙的默认通信波特率以及蓝牙默认的名字******************/
//	uart3_init(9600);//先9600  
//	delay_ms(100);
//	USART3_Send_String("AT\r\n");
//	USART3_Send_String("AT+NAME Walk the world\r\n");//发送蓝牙模块指令--设置名字
//	delay_ms(100);	
//	USART3_Send_String("AT+BAUD8\r\n"); 		 //发送蓝牙模块指令,将波特率设置成115200
//	delay_ms(100);		
//	uart3_init(115200);//再修为115200
//	/*****************************************************************************/
