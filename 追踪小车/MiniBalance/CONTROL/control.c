#include "control.h"	
#include "motor.h"
#include "openmv.h"
  /**************************************************************************

**************************************************************************/
CAR_STATUS_e car_mode=stop;  //����״̬     extern volatile
int16 x_error=0;
int16 last_x_error=0; 
int16 ser_duty=0;
uint8 out_edge=0;//����
float C_P=4; //cameraP
float C_D=0; //cameraD
moty_duty run_duty={0};//����ftm����ٶ�

void Car_mode_control(void)
{
		if(OpenMV_RX>130 && OpenMV_RX!=0) //�����
		{
			
			out_edge=Left;//0��
		}
		else if(OpenMV_RX<30 && OpenMV_RX!=0) //�ҳ���
		{
			LED=0;
			out_edge=Right;//1��
		}
		else if(OpenMV_RX>30 && OpenMV_RX<130 ) //�ҳ���
		{
			LED=1;
			out_edge=run;//run=2
		}
		//��λ״̬�ж�
		if(out_edge==Left && OpenMV_L>10)
		{
			
			car_mode=finding_L;//finding_L = 3
		}
		else if(out_edge==Right && OpenMV_L>10)
		{
			
			car_mode=finding_R;//finding_R = 4
		}
		else if(out_edge==run&& OpenMV_L>10)
		{
			
			car_mode=run;//run=2
		}
		else if(OpenMV_L<=10 && OpenMV_L>=5)
		{	
			
			car_mode=stop;//stop = 1
		}
		

		
}
	

void move_updata(void)
{
		//12
		if(car_mode == run)
		{
			
			
						IN1 = 0;
						IN2 = 1;
						IN3 = 0;
						IN4 = 1;
		}
		else if(car_mode == finding_R)
		{
			
						IN1 = 1;
						IN2 = 0;
						IN3 = 0;
						IN4 = 1;			
			
			
		}
		else if(car_mode == finding_L)
		{
			
						IN1 = 0;
						IN2 = 1;
						IN3 = 1;
						IN4 = 0;
		}
	  else if(car_mode == stop)
		{
						IN1 = 0;
						IN2 = 0;
						IN3 = 0;
						IN4 = 0;
		}
}


void PD_control(void)
{

	last_x_error=x_error;
	x_error=OpenMV_RX-160;
	ser_duty = C_P*x_error-C_D*(last_x_error-x_error);

	run_duty.Speed_Duty_R=255-ser_duty;//��Ϊ��ת
	run_duty.Speed_Duty_L=255-ser_duty;
	//���FTM��//�޷�	
	run_duty.Speed_Duty_L=run_duty.Speed_Duty_L<30?30:run_duty.Speed_Duty_L;
	run_duty.Speed_Duty_L=run_duty.Speed_Duty_L>220?220:run_duty.Speed_Duty_L;
	//�ұ�FTM��//�޷�	
  run_duty.Speed_Duty_R=run_duty.Speed_Duty_R<30?30:run_duty.Speed_Duty_R;
	run_duty.Speed_Duty_R=run_duty.Speed_Duty_R>220?220:run_duty.Speed_Duty_R;

	PWM_Config(run_duty.Speed_Duty_R,run_duty.Speed_Duty_L);
	
}

