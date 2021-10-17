#include "stm32f10x.h"
#include "sys.h" 

float Pitch,Roll,Yaw;						//�Ƕ�
short gyrox,gyroy,gyroz;				//������--���ٶ�
short aacx,aacy,aacz;						//���ٶ�
int Encoder_Left,Encoder_Right;	//���������ݣ��ٶȣ�

int PWM_MAX=7200,PWM_MIN=-7200;	//PWM�޷�����
int MOTO1,MOTO2;								//���װ�ر���

extern int Vertical_out,Velocity_out,Turn_out;
int main(void)	
{
	delay_init();
	NVIC_Config();
	uart1_init(115200);	
	
	//һ��//
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



////����////���������Ĭ�ϲ����ʲ���115200�����������ֱ���滻�����桰һ�������ɡ�
//	/*****************������Ĭ�ϲ�����Ϊ9600����������9600�����޸�������Ĭ��ͨ�Ų������Լ�����Ĭ�ϵ�����******************/
//	uart3_init(9600);//��9600  
//	delay_ms(100);
//	USART3_Send_String("AT\r\n");
//	USART3_Send_String("AT+NAME Walk the world\r\n");//��������ģ��ָ��--��������
//	delay_ms(100);	
//	USART3_Send_String("AT+BAUD8\r\n"); 		 //��������ģ��ָ��,�����������ó�115200
//	delay_ms(100);		
//	uart3_init(115200);//����Ϊ115200
//	/*****************************************************************************/
