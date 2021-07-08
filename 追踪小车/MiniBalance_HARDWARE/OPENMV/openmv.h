#ifndef __OPENMV_H
#define __OPENMV_H

#include "sys.h"

extern int16_t OpenMV_RX;
extern int16_t OpenMV_RY;
extern int8_t OpenMV_L;
extern int8_t OpenMV_GY;
extern int8_t OpenMV_add;
extern int openmv[8];//stm32接收数据数组




void Openmv_Receive_Data(int16_t data);
void Openmv_Data(void);

#endif
