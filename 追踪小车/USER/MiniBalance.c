#include "stm32f10x.h"
#include "sys.h"
#include "usart.h"
#include "control.h"
#include "motor.h"
  /**************************************************************************

**************************************************************************/
 
int main(void)
  { 
		delay_init();	    	            //=====��ʱ������ʼ��	
		uart_init(115200);	            //=====���ڳ�ʼ��Ϊ
		JTAG_Set(JTAG_SWD_DISABLE);     //=====�ر�JTAG�ӿ�
		JTAG_Set(SWD_ENABLE);           //=====��SWD�ӿ� �������������SWD�ӿڵ���
		LED_Init();                     //=====��ʼ���� LED ���ӵ�Ӳ���ӿ�
	  KEY_Init();                     //=====������ʼ��
		MY_NVIC_PriorityGroupConfig(2);	//=====�����жϷ���b
		TIM_Cmd(TIM1, ENABLE);  //ʹ��TIM1
		IIC_Init();                     //=====IIC��ʼ��
    //MPU6050_initialize();           //=====MPU6050��ʼ��	
    OLED_Init();                    //=====OLED��ʼ��	 
						
    while(1)
	   {
//			 			IN1 = 0;
//						IN2 = 0;
//						IN3 = 1;
//						IN4 = 0;
//			LED=0;
			PWM_INIT();
			Car_mode_control();
			move_updata();
			PD_control();
			oled_show();          //===��ʾ����
				
	   } 
} 

