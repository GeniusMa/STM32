#include "control.h"

float Med_Angle=-1;		
float Target_Speed=0;	
float Turn_Speed=0;		
float 
	Vertical_Kp=204,
	Vertical_Kd=0.78;
float 
	Velocity_Kp=0.56,
	Velocity_Ki=0.0028;
float 
	Turn_Kd=0.6,
	Turn_Kp=20;

#define SPEED_Y 30 
#define SPEED_Z 100

int Vertical_out,Velocity_out,Turn_out;

int Vertical(float Med,float Angle,float gyro_Y);
int Velocity(int Target,int encoder_left,int encoder_right);
int Turn(int gyro_Z,int RC); 

void EXTI9_5_IRQHandler(void)
{
	int PWM_out;
	if(EXTI_GetITStatus(EXTI_Line5)!=0)
	{
		if(PBin(5)==0)
		{
			EXTI_ClearITPendingBit(EXTI_Line5);
			Encoder_Left=-Read_Speed(2);
			Encoder_Right=Read_Speed(4);
			mpu_dmp_get_data(&Pitch,&Roll,&Yaw);			
			MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	
			MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	
		
			if((Fore==0)&&(Back==0))Target_Speed=0;
			if(Fore==1)Target_Speed-=50;
			if(Back==1)Target_Speed+=50;
			Target_Speed=Target_Speed>SPEED_Y?SPEED_Y:(Target_Speed<-SPEED_Y?(-SPEED_Y):Target_Speed);	
			if((Left==0)&&(Right==0))Turn_Speed=0;
			if(Left==1)Turn_Speed+=30;	
			if(Right==1)Turn_Speed-=30;	
			Turn_Speed=Turn_Speed>SPEED_Z?SPEED_Z:(Turn_Speed<-SPEED_Z?(-SPEED_Z):Turn_Speed);
			if((Left==0)&&(Right==0))Turn_Kd=0.6;
			else if((Left==1)||(Right==1))Turn_Kd=0;
			
			Velocity_out=Velocity(Target_Speed,Encoder_Left,Encoder_Right);	
			Vertical_out=Vertical(Velocity_out+Med_Angle,Pitch,gyroy);			
			Turn_out=Turn(gyroz,Turn_Speed);																
			
			PWM_out=Vertical_out;
			MOTO1=PWM_out-Turn_out;
			MOTO2=PWM_out+Turn_out;
			Limit(&MOTO1,&MOTO2);	 			
			Load(MOTO1,MOTO2);		 
			Stop(&Med_Angle,&Pitch);
			
		}
	}
}




/*********************
直立环PD控制器：Kp*Ek+Kd*Ek_D
形参：期望角度、真实角度、真实角速度
返还值：直立环输出
*********************/
int Vertical(float Med,float Angle,float gyro_Y)
{
	int PWM_out;
	
	PWM_out=Vertical_Kp*(Angle-Med)+Vertical_Kd*(gyro_Y-0);
	return PWM_out;
}


/*********************
速度环PI：Kp*Ek+Ki*Ek_S
形参：期望速度，左电机速度，右电机速度
返还值：直立环输入
*********************/
int Velocity(int Target,int encoder_left,int encoder_right)
{
	static int Encoder_S,EnC_Err_Lowout_last,PWM_out,Encoder_Err,EnC_Err_Lowout;
	float a=0.7;
	Encoder_Err=((encoder_left+encoder_right)-Target);
	EnC_Err_Lowout=(1-a)*Encoder_Err+a*EnC_Err_Lowout_last;
	EnC_Err_Lowout_last=EnC_Err_Lowout;
	Encoder_S+=EnC_Err_Lowout;
	Encoder_S=Encoder_S>10000?10000:(Encoder_S<(-10000)?(-10000):Encoder_S);
	if(stop==1)Encoder_S=0,stop=0;
	PWM_out=Velocity_Kp*EnC_Err_Lowout+Velocity_Ki*Encoder_S;
	return PWM_out;
}


/*********************
转向环：系数*Z轴角速度+系数*遥控数据
*********************/
int Turn(int gyro_Z,int RC)
{
	int PWM_out;
	PWM_out=Turn_Kd*gyro_Z + Turn_Kp*RC;
	return PWM_out;
}

