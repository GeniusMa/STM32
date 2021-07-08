#include "control.h"	
/**************************************************************************
 ×÷  Õß £º´óÓãµç×Ó
 ÌÔ±¦µØÖ·£ºhttps://shop119207236.taobao.com
 Î¢ĞÅ¹«ÖÚºÅ¡¾´óÓã»úÆ÷ÈË¡¿
 ºóÌ¨»Ø¸´¡¾Æ½ºâĞ¡³µ¡¿£º»ñÈ¡Æ½ºâĞ¡³µÈ«Ì×DIY×ÊÁÏ
 ºóÌ¨»Ø¸´¡¾µç×Ó¿ª·¢¹¤¾ß¡¿£º»ñÈ¡µç×Ó¹¤³ÌÊ¦±Ø±¸¿ª·¢¹¤¾ß
 ºóÌ¨»Ø¸´¡¾µç×ÓÉè¼Æ×ÊÁÏ¡¿£º»ñÈ¡µç×ÓÉè¼Æ×ÊÁÏ°ü
 Öªºõ£ºÕÅÇÉÁú 
**************************************************************************/
/**************************************************************************
º¯Êı¹¦ÄÜ£ºËùÓĞµÄ¿ØÖÆ´úÂë¶¼ÔÚÕâÀïÃæ
         5ms¶¨Ê±ÖĞ¶ÏÓÉMPU6050µÄINTÒı½Å´¥·¢
         ÑÏ¸ñ±£Ö¤²ÉÑùºÍÊı¾İ´¦ÀíµÄÊ±¼äÍ¬²½	
				 ÔÚMPU6050µÄ²ÉÑùÆµÂÊÉèÖÃÖĞ£¬ÉèÖÃ³É100HZ£¬¼´¿É±£Ö¤6050µÄÊı¾İÊÇ10ms¸üĞÂÒ»´Î¡£
				 ¶ÁÕß¿ÉÔÚimv_mpu.hÎÄ¼şµÚ26ĞĞµÄºê¶¨Òå½øĞĞĞŞ¸Ä(#define DEFAULT_MPU_HZ  (100))
**************************************************************************/
int Balance_Pwm,Velocity_Pwm,Turn_Pwm;

float Mechanical_angle=6; 

float balance_UP_KP=240; 	 // Ğ¡³µÖ±Á¢»·PD²ÎÊı
float balance_UP_KD=1.32;

float velocity_KP=0.65;     // Ğ¡³µËÙ¶È»·PI²ÎÊı
float velocity_KI=0.00325;

u8 UltrasonicWave_Voltage_Counter=0;

void EXTI9_5_IRQHandler(void) 
{    
	if(PBin(5)==0)		
	{		
		EXTI->PR=1<<5;                                           //===Çå³ıLINE5ÉÏµÄÖĞ¶Ï±êÖ¾Î»   
		mpu_dmp_get_data(&pitch,&roll,&yaw);										 //===µÃµ½Å·À­½Ç£¨×ËÌ¬½Ç£©µÄÊı¾İ
		MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);								 //===µÃµ½ÍÓÂİÒÇÊı¾İ
		Encoder_Left=-Read_Encoder(2);                           //===¶ÁÈ¡±àÂëÆ÷µÄÖµ£¬ÒòÎªÁ½¸öµç»úµÄĞı×ªÁË180¶ÈµÄ£¬ËùÒÔ¶ÔÆäÖĞÒ»¸öÈ¡·´£¬±£Ö¤Êä³ö¼«ĞÔÒ»ÖÂ
		Encoder_Right=Read_Encoder(4);                           //===¶ÁÈ¡±àÂëÆ÷µÄÖµ
		UltrasonicWave_Voltage_Counter++;
		if(UltrasonicWave_Voltage_Counter==10)									 //===100ms¶ÁÈ¡Ò»´Î³¬Éù²¨µÄÊı¾İÒÔ¼°µçÑ¹
		{
			UltrasonicWave_Voltage_Counter=0;
			Voltage=Get_battery_volt();		                         //===¶ÁÈ¡µç³ØµçÑ¹		
			UltrasonicWave_StartMeasure();												 //===¶ÁÈ¡³¬Éù²¨µÄÖµ
		}
		Balance_Pwm =balance_UP(pitch,Mechanical_angle,gyroy);   //===Æ ½ºâ»·PID¿ØÖÆ	
		Velocity_Pwm=velocity(Encoder_Left,Encoder_Right);       //===ËÙ¶È»·PID¿ØÖÆ	 
  	if(1==Flag_Left||1==Flag_Right)    
		Turn_Pwm =turn(Encoder_Left,Encoder_Right,gyroz);        //===×ªÏò»·PID¿ØÖÆ
		else Turn_Pwm=-0.5*gyroz;
		Moto1=Balance_Pwm-Velocity_Pwm-Turn_Pwm;                 //===¼ÆËã×óÂÖµç»ú×îÖÕPWM
		Moto2=Balance_Pwm-Velocity_Pwm+Turn_Pwm;                 //===¼ÆËãÓÒÂÖµç»ú×îÖÕPWM
	  Xianfu_Pwm();  																					 //===PWMÏŞ·ù
		Turn_Off(pitch,12);																 //===¼ì²é½Ç¶ÈÒÔ¼°µçÑ¹ÊÇ·ñÕı³£
		Set_Pwm(Moto1,Moto2);                                    //===¸³Öµ¸øPWM¼Ä´æÆ÷  
	}       	
} 

/**************************************************************************
º¯Êı¹¦ÄÜ£ºÖ±Á¢PD¿ØÖÆ
Èë¿Ú²ÎÊı£º½Ç¶È¡¢»úĞµÆ½ºâ½Ç¶È£¨»úĞµÖĞÖµ£©¡¢½ÇËÙ¶È
·µ»Ø  Öµ£ºÖ±Á¢¿ØÖÆPWM
×÷    Õß£º´óÓãµç×Ó
**************************************************************************/
int balance_UP(float Angle,float Mechanical_balance,float Gyro)
{  
   float Bias;
	 int balance;
	 Bias=Angle-Mechanical_balance;    							 //===Çó³öÆ½ºâµÄ½Ç¶ÈÖĞÖµºÍ»úĞµÏà¹Ø
	 balance=balance_UP_KP*Bias+balance_UP_KD*Gyro;  //===¼ÆËãÆ½ºâ¿ØÖÆµÄµç»úPWM  PD¿ØÖÆ   kpÊÇPÏµÊı kdÊÇDÏµÊı 
	 return balance;
}

/**************************************************************************
º¯Êı¹¦ÄÜ£ºËÙ¶ÈPI¿ØÖÆ
Èë¿Ú²ÎÊı£ºµç»ú±àÂëÆ÷µÄÖµ
·µ»Ø  Öµ£ºËÙ¶È¿ØÖÆPWM
×÷    Õß£º´óÓãµç×Ó
**************************************************************************/
int velocity(int encoder_left,int encoder_right)
{  
    static float Velocity,Encoder_Least,Encoder,Movement;
	  static float Encoder_Integral;
		if(1==Flag_Qian)				
		{
			flag_UltrasonicWave=0;//ÎŞÂÛÇ°ÃæÊÇ·ñÓĞÕÏ°­Îï,À¶ÑÀÒ£¿ØÓÅÏÈ¼¶×î¸ß¡£½«±êÖ¾Î»ÖÃ0
			Movement=-150;
		}
    else if(1==Flag_Hou)//½ÓÊÕµ½À¶ÑÀAPPÒ£¿ØÊı¾İ		
		{
			flag_UltrasonicWave=0;//ÎŞÂÛÇ°ÃæÊÇ·ñÓĞÕÏ°­Îï,À¶ÑÀÒ£¿ØÓÅÏÈ¼¶×î¸ß¡£½«±êÖ¾Î»ÖÃ0
			Movement=150;//Éè¶¨ËÙ¶È
		}
		/*µ±³¬Éù²¨µÄ¾àÀëµÍÓÚ10cmÊ±,¼´10cm´¦´æÔÚÕÏ°­Îï,½«³¬Éù²¨±êÖ¾Î»ÖÃ²¢ÇÒ¸³»ı·ÖÖµÊ¹ÆäºóÍË,ÕâÀï×öÁË¸ö¼òµ¥µÄP±ÈÀı¼ÆËã*/
		//else if(UltrasonicWave_Distance<10&&UltrasonicWave_Distance>3)
		//{
		//	flag_UltrasonicWave=1;
		//	Movement=UltrasonicWave_Distance*50;		
		//}
		else//Ã»ÓĞ½ÓÊÜµ½ÈÎºÎµÄÊı¾İ
		{	
			flag_UltrasonicWave=0;
			Movement=0;
		}
   //=============ËÙ¶ÈPI¿ØÖÆÆ÷=======================//	
		Encoder_Least =(Encoder_Left+Encoder_Right)-0;                    //===»ñÈ¡×îĞÂËÙ¶ÈÆ«²î==²âÁ¿ËÙ¶È£¨×óÓÒ±àÂëÆ÷Ö®ºÍ£©-Ä¿±êËÙ¶È£¨´Ë´¦ÎªÁã£© 
		Encoder *= 0.8;		                                                //===Ò»½×µÍÍ¨ÂË²¨Æ÷       
		Encoder += Encoder_Least*0.2;	                                    //===Ò»½×µÍÍ¨ÂË²¨Æ÷    
		Encoder_Integral +=Encoder;                                       //===»ı·Ö³öÎ»ÒÆ »ı·ÖÊ±¼ä£º10ms
		Encoder_Integral=Encoder_Integral-Movement;                       //===½ÓÊÕÒ£¿ØÆ÷Êı¾İ£¬¿ØÖÆÇ°½øºóÍË
		if(Encoder_Integral>10000)  	Encoder_Integral=10000;             //===»ı·ÖÏŞ·ù
		if(Encoder_Integral<-10000)		Encoder_Integral=-10000;            //===»ı·ÖÏŞ·ù	
		Velocity=Encoder*velocity_KP+Encoder_Integral*velocity_KI;        //===ËÙ¶È¿ØÖÆ	
	  if(pitch<-40||pitch>40) 			Encoder_Integral=0;     						//===µç»ú¹Ø±ÕºóÇå³ı»ı·Ö
	  return Velocity;
}
/**************************************************************************
º¯Êı¹¦ÄÜ£º×ªÏòPD¿ØÖÆ
Èë¿Ú²ÎÊı£ºµç»ú±àÂëÆ÷µÄÖµ¡¢ZÖá½ÇËÙ¶È
·µ»Ø  Öµ£º×ªÏò¿ØÖÆPWM
×÷    Õß£º´óÓãµç×Ó
**************************************************************************/
int turn(int encoder_left,int encoder_right,float gyro)//×ªÏò¿ØÖÆ
{
	 static float Turn_Target,Turn,Encoder_temp,Turn_Convert=0.9,Turn_Count;
	  float Turn_Amplitude=100,Kp=20,Kd=0;     
	  //=============Ò£¿Ø×óÓÒĞı×ª²¿·Ö=======================//
	  //ÕâÒ»²¿·ÖÖ÷ÒªÊÇ¸ù¾İĞı×ªÇ°µÄËÙ¶Èµ÷ÕûËÙ¶ÈµÄÆğÊ¼ËÙ¶È£¬Ôö¼ÓĞ¡³µµÄÊÊÓ¦ĞÔ
  	if(1==Flag_Left||1==Flag_Right)                      
		{
			if(++Turn_Count==1)
			Encoder_temp=myabs(encoder_left+encoder_right);      
			Turn_Convert=55/Encoder_temp;
			if(Turn_Convert<0.6)Turn_Convert=0.6;
			if(Turn_Convert>3)Turn_Convert=3;
		}	
	  else
		{
			Turn_Convert=0.9;
			Turn_Count=0;
			Encoder_temp=0;
		}			
		if(1==Flag_Left)	           Turn_Target+=Turn_Convert;
		else if(1==Flag_Right)	     Turn_Target-=Turn_Convert; 
		else Turn_Target=0;
    if(Turn_Target>Turn_Amplitude)  Turn_Target=Turn_Amplitude;    //===×ªÏò	ËÙ¶ÈÏŞ·ù
	  if(Turn_Target<-Turn_Amplitude) Turn_Target=-Turn_Amplitude;
		if(Flag_Qian==1||Flag_Hou==1)  Kd=0.5;        
		else Kd=0;   //×ªÏòµÄÊ±ºòÈ¡ÏûÍÓÂİÒÇµÄ¾ÀÕı ÓĞµãÄ£ºıPIDµÄË¼Ïë
  	//=============×ªÏòPD¿ØÖÆÆ÷=======================//
		Turn=-Turn_Target*Kp-gyro*Kd;                 //===½áºÏZÖáÍÓÂİÒÇ½øĞĞPD¿ØÖÆ
	  return Turn;
}
