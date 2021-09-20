#ifndef __USART_H
#define __USART_H

#include "stm32f10x.h"
#include <stdio.h>



void usart_config();
void Usart_SendByte(USART_TypeDef *pUSARTx,uint8_t data);
void Usart_Send_HlafWord( USART_TypeDef * pUSARTx, uint16_t data);
void Usart_Send_Arr(USART_TypeDef * pUSARTx, uint8_t data[],uint8_t num);
void Usart_Send_String(USART_TypeDef * pUSARTx, uint8_t* p);
int fgetc(FILE *f);
int fputc(int ch, FILE *f);
#endif /*__USART_H*/


