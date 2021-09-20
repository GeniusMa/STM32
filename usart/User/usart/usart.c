#include "usart.h"

static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void usart_config()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);

	NVIC_Configuration();
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	

	USART_Cmd(USART1, ENABLE);	
}

void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t data)
{
	USART_SendData(pUSARTx,data);
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == 0);	
}

void Usart_Send_HlafWord( USART_TypeDef * pUSARTx, uint16_t data)
{
	uint8_t tmpH,tmpL;
	tmpH = (data&0xff00)>>8;
	tmpL = data&0xff;
	USART_SendData(pUSARTx,tmpH);
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == 0);	
	USART_SendData(pUSARTx,tmpL);
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == 0);		
}

void Usart_Send_Arr(USART_TypeDef * pUSARTx, uint8_t data[],uint8_t num)
{
	uint8_t i;
	for(i=0;i<num;i++)
	{
			USART_SendData(pUSARTx,data[i]);
			while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == 0);		
	}
}

void Usart_Send_String(USART_TypeDef * pUSARTx, uint8_t* p)
{
	uint8_t i=0;
	do
	{
		USART_SendData(pUSARTx,*(p+i));
		i++;
		while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == 0);	
	}while(*(p+i)!='\0');
}

///重定向c库函数printf到串口，重定向后可使用printf函数
int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到串口 */
		USART_SendData(USART1, (uint8_t) ch);
		
		/* 等待发送完毕 */
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

///重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{
		/* 等待串口输入数据 */
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USART1);
}


