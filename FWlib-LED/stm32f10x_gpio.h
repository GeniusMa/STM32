#ifndef __STM32F10X_GPIO_H
#define __STM32F10X_GPIO_H

#include "stm32f10x.h"

#define GPIO_Pin_0    ((uint16_t)0x0001)  /*!< ѡ��Pin0 */    //(00000000 00000001)b
#define GPIO_Pin_1    ((uint16_t)0x0002)  /*!< ѡ��Pin1 */    //(00000000 00000010)b
#define GPIO_Pin_2    ((uint16_t)0x0004)  /*!< ѡ��Pin2 */    //(00000000 00000100)b
#define GPIO_Pin_3    ((uint16_t)0x0008)  /*!< ѡ��Pin3 */    //(00000000 00001000)b
#define GPIO_Pin_4    ((uint16_t)0x0010)  /*!< ѡ��Pin4 */    //(00000000 00010000)b
#define GPIO_Pin_5    ((uint16_t)0x0020)  /*!< ѡ��Pin5 */    //(00000000 00100000)b
#define GPIO_Pin_6    ((uint16_t)0x0040)  /*!< ѡ��Pin6 */    //(00000000 01000000)b
#define GPIO_Pin_7    ((uint16_t)0x0080)  /*!< ѡ��Pin7 */    //(00000000 10000000)b

#define GPIO_Pin_8    ((uint16_t)0x0100)  /*!< ѡ��Pin8 */    //(00000001 00000000)b
#define GPIO_Pin_9    ((uint16_t)0x0200)  /*!< ѡ��Pin9 */    //(00000010 00000000)b
#define GPIO_Pin_10   ((uint16_t)0x0400)  /*!< ѡ��Pin10 */   //(00000100 00000000)b
#define GPIO_Pin_11   ((uint16_t)0x0800)  /*!< ѡ��Pin11 */   //(00001000 00000000)b
#define GPIO_Pin_12   ((uint16_t)0x1000)  /*!< ѡ��Pin12 */   //(00010000 00000000)b
#define GPIO_Pin_13   ((uint16_t)0x2000)  /*!< ѡ��Pin13 */   //(00100000 00000000)b
#define GPIO_Pin_14   ((uint16_t)0x4000)  /*!< ѡ��Pin14 */   //(01000000 00000000)b
#define GPIO_Pin_15   ((uint16_t)0x8000)  /*!< ѡ��Pin15 */   //(10000000 00000000)b
#define GPIO_Pin_All  ((uint16_t)0xFFFF)  /*!< ѡ��ȫ������*/ //(11111111 11111111)b

typedef enum
{
	GPIO_Speed_10MHZ = 1,     // 10MHZ    (01)b
	GPIO_Speed_2MHZ,          //2MHZ      (10)b
	GPIO_Speed_50MHZ          //50MHZ     (11)b
} GPIOSpeed_TypeDef;

/**
 *GPIO
 */
typedef enum
{
	GPIO_Mode_AIN=0X0,
	GPIO_Mode_IN_FLOATING=0X04,
	GPIO_Mode_IPD=0X28,
	GPIO_Mode_IPU=0X48,
	
	GPIO_Mode_OUT_OD=0X14,
	GPIO_Mode_OUT_PP=0X10,
	GPIO_Mode_AF_OD=0X1C,
	GPIO_Mode_AF_PP=0X18,
}GPIOMode_TypeDef;


typedef struct
{
	uint16_t GPIO_Pin;
	uint16_t GPIO_Speed;
	uint16_t GPIO_Mode;
}GPIO_InitTypeDef;



void GPIO_SetBits(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin);
void GPIO_ResetBits( GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin );
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);


#endif /* __STM32F10X_GPIO_H */

