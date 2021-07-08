#ifndef __BSP_DMA_MTM_H
#define __BSP_DMA_MTM_H

#include "stm32f10x.h"

#define DMA_MTM_CLK RCC_AHBPeriph_DMA1
#define DMA_MTM_CHANNEL DMA1_Channel6
#define BUFFER_SIZE   32

void MtM_DMA_Config(void);
uint8_t Buffercmp(const uint32_t* pBuffer, 
                  uint32_t* pBuffer1, uint16_t BufferLength);

#endif  /*__BSP_DMA_MTM_H*/
