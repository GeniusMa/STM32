#include "stm32f10x.h"
#include "sys.h"
#include "usart.h"
#include "control.h"
#include "motor.h"
  /**************************************************************************

**************************************************************************/
 
int main(void)
  { 
		delay_init();	    	            //=====延时函数初始化	
		uart_init(115200);	            //=====串口初始化为
		JTAG_Set(JTAG_SWD_DISABLE);     //=====关闭JTAG接口
		JTAG_Set(SWD_ENABLE);           //=====打开SWD接口 可以利用主板的SWD接口调试
		LED_Init();                     //=====初始化与 LED 连接的硬件接口
	  KEY_Init();                     //=====按键初始化
		MY_NVIC_PriorityGroupConfig(2);	//=====设置中断分组b
		TIM_Cmd(TIM1, ENABLE);  //使能TIM1
		IIC_Init();                     //=====IIC初始化
    //MPU6050_initialize();           //=====MPU6050初始化	
    OLED_Init();                    //=====OLED初始化	 
						
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
			oled_show();          //===显示屏打开
				
	   } 
} 

