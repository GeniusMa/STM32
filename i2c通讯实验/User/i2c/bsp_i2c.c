#include "bsp_i2c.h"


void I2C_EE_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	I2C_InitTypeDef  I2C_InitStructure;

	// 打开I2C GPIO的时钟
	EEPROM_I2C_GPIO_APBxClkCmd(EEPROM_I2C_SCL_GPIO_CLK|EEPROM_I2C_SDA_GPIO_CLK, ENABLE);
	
	// 打开I2C 外设的时钟
	EEPROM_I2C_APBxClkCmd (EEPROM_I2C_CLK , ENABLE);

	// 初始化 SCL GPIO
	GPIO_InitStructure.GPIO_Pin = EEPROM_I2C_SCL_GPIO_PIN ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(EEPROM_I2C_SCL_GPIO_PORT, &GPIO_InitStructure);

  // 将SDA的GPIO配置
	GPIO_InitStructure.GPIO_Pin = EEPROM_I2C_SDA_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_Init(EEPROM_I2C_SDA_GPIO_PORT, &GPIO_InitStructure);
	
	//初始化 I2C
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable ;
	I2C_InitStructure.I2C_AcknowledgedAddress=I2C_AcknowledgedAddress_7bit ;
	I2C_InitStructure.I2C_ClockSpeed=EEPROM_I2C_BAUDRATE ;
	I2C_InitStructure.I2C_DutyCycle=I2C_DutyCycle_2 ;
	I2C_InitStructure.I2C_Mode=I2C_Mode_I2C  ;
	I2C_InitStructure.I2C_OwnAddress1=I2C_OWN_ADDR ;
	I2C_Init(EEPROM_I2C ,&I2C_InitStructure);
	
	
	// 使能i2c
	I2C_Cmd(EEPROM_I2C, ENABLE);	    
}


//向eeprom写入一个字节
void EEPROM_Byte_Write(uint8_t addr,uint8_t data)
{
	I2C_GenerateSTART(EEPROM_I2C,ENABLE);
	while(I2C_CheckEvent(EEPROM_I2C,I2C_EVENT_MASTER_MODE_SELECT)==ERROR);
	I2C_Send7bitAddress(EEPROM_I2C,EEPROM_ADDR ,I2C_Direction_Transmitter);
	while(I2C_CheckEvent(EEPROM_I2C,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)==ERROR);
	I2C_SendData(EEPROM_I2C,addr);
	while(I2C_CheckEvent(EEPROM_I2C,I2C_EVENT_MASTER_BYTE_TRANSMITTING )==ERROR);
	I2C_SendData(EEPROM_I2C,data);
	while(I2C_CheckEvent(EEPROM_I2C,I2C_EVENT_MASTER_BYTE_TRANSMITTED )==ERROR);
	I2C_GenerateSTOP (EEPROM_I2C,ENABLE);
}

void EEPROM_Page_Write(uint8_t addr,uint8_t *data,uint8_t numByteToWrite)
{
	I2C_GenerateSTART(EEPROM_I2C,ENABLE);
	while(I2C_CheckEvent(EEPROM_I2C,I2C_EVENT_MASTER_MODE_SELECT)==ERROR);
	I2C_Send7bitAddress(EEPROM_I2C,EEPROM_ADDR ,I2C_Direction_Transmitter);
	while(I2C_CheckEvent(EEPROM_I2C,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)==ERROR);
	I2C_SendData(EEPROM_I2C,addr);
	while(I2C_CheckEvent(EEPROM_I2C,I2C_EVENT_MASTER_BYTE_TRANSMITTING )==ERROR);
	while(numByteToWrite)
	{
		I2C_SendData(EEPROM_I2C,*data);
		while(I2C_CheckEvent(EEPROM_I2C,I2C_EVENT_MASTER_BYTE_TRANSMITTED )==ERROR);
		I2C_GenerateSTOP (EEPROM_I2C,ENABLE);
		data++;
		numByteToWrite--;
	}
	I2C_GenerateSTOP (EEPROM_I2C,ENABLE); 
}




void EEPROM_Read(uint8_t addr,uint8_t *data,uint8_t numByteToRead)
{
	I2C_GenerateSTART(EEPROM_I2C,ENABLE);
	while(I2C_CheckEvent(EEPROM_I2C,I2C_EVENT_MASTER_MODE_SELECT)==ERROR);
	I2C_Send7bitAddress(EEPROM_I2C,EEPROM_ADDR ,I2C_Direction_Transmitter);
	while(I2C_CheckEvent(EEPROM_I2C,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)==ERROR);
	I2C_SendData(EEPROM_I2C,addr);
	while(I2C_CheckEvent(EEPROM_I2C,I2C_EVENT_MASTER_BYTE_TRANSMITTING )==ERROR);
	
	I2C_GenerateSTART(EEPROM_I2C,ENABLE);
	while(I2C_CheckEvent(EEPROM_I2C,I2C_EVENT_MASTER_MODE_SELECT)==ERROR);
	I2C_Send7bitAddress(EEPROM_I2C,EEPROM_ADDR ,I2C_Direction_Receiver);
	while(I2C_CheckEvent(EEPROM_I2C,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED )==ERROR);
	
	while(numByteToRead)
	{
				
		if(numByteToRead == 1)
		{
			I2C_AcknowledgeConfig(EEPROM_I2C,DISABLE);
			
		}
		while(I2C_CheckEvent(EEPROM_I2C,I2C_EVENT_MASTER_BYTE_RECEIVED  )==ERROR);
		
		*data = I2C_ReceiveData(EEPROM_I2C);
		
		data++;
		numByteToRead--;
	
	}
	I2C_GenerateSTOP (EEPROM_I2C,ENABLE);
	I2C_AcknowledgeConfig(EEPROM_I2C,ENABLE);
}



void EEPROM_WaitForWritrEnd(void)
{
	do
	{
	I2C_GenerateSTART(EEPROM_I2C,ENABLE);
	while(I2C_GetFlagStatus (EEPROM_I2C,I2C_FLAG_SB)==RESET);
	I2C_Send7bitAddress(EEPROM_I2C,EEPROM_ADDR ,I2C_Direction_Transmitter);
	}
	while(I2C_GetFlagStatus (EEPROM_I2C,I2C_FLAG_ADDR)==RESET);
	
	I2C_GenerateSTOP (EEPROM_I2C,ENABLE);
}
