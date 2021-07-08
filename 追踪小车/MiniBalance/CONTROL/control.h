#ifndef __CONTROL_H
#define __CONTROL_H
#include "sys.h"
  /**************************************************************************

**************************************************************************/
typedef unsigned char       uint8;  /*  8 bits */
typedef unsigned short int  uint16; /* 16 bits */
typedef unsigned long int   uint32; /* 32 bits */
typedef unsigned long long  uint64; /* 64 bits */

typedef char                int8;   /*  8 bits */
typedef short int           int16;  /* 16 bits */
typedef long  int           int32;  /* 32 bits */
typedef long  long          int64;  /* 64 bits */

#define Left  0  //0左1右
#define Right 1
 
typedef enum   //枚举
{
	finding_R=4,
	finding_L=3,
	run=2,
	stop=1,
	error=0,
}
CAR_STATUS_e;  //车子状态 


typedef struct D  //结构体
{
	int16 Speed_Duty_L;
	int16 Speed_Duty_R;
}moty_duty;




void Car_mode_control(void);
void move_updata(void);
void PD_control(void);


#endif
