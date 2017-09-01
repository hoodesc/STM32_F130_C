#include "stm32f10x.h"
#include "IIC.h"
#include "sys.h"
#include "delay.h"

#define IIC_SCL PBout(0)
#define IIC_SDA PBout(1)
#define READ_SDA PBin(1)



void IIC_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;	//	????
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

u8 IIC_Start()
{
	IIC_SDA=1;
	IIC_SCL=1;
	delay_us(2);
	if(!READ_SDA)
		return FALSE;
	IIC_SDA=0;
	delay_us(2);
	if(READ_SDA)
		return FALSE;
	IIC_SCL=0;
	delay_us(2);
	return TRUE;
}

void IIC_Stop()
{
	IIC_SDA=0;
	IIC_SCL=1;
	delay_us(2);
	IIC_SDA=1;
	delay_us(2);
}

void IIC_Ack()
{
	IIC_SCL = 0;
	IIC_SDA = 0;
	delay_us(2);
	IIC_SCL = 1;
	delay_us(2);
	IIC_SCL = 0;
}
void IIC_NoAck()
{
	IIC_SCL=0;
	IIC_SDA=1;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}
u8 IIC_Wait_Ack()
{
	u8 delaytime;
	IIC_SCL = 0;
	delay_us(2);
	IIC_SDA = 1;
	delay_us(2);	
	IIC_SCL = 1;
	while(READ_SDA)
	{
		delaytime++;
		if(delaytime > 250)
		{
			IIC_Stop();
			return FALSE;
		}
	}
	IIC_SCL = 0;
	delay_us(2);	
	return TRUE;
}

void IIC_Send_a_Byte(u8 dat)
{
	u8 i;
	for(i = 0; i < 8; i++)
	{
		IIC_SCL = 0;
		delay_us(2);
		IIC_SDA = (dat&0x80)>>7;
		delay_us(2);
		IIC_SCL = 1;
		delay_us(2);
		IIC_SCL = 0;
		delay_us(2);
		dat <<= 1;
	}
}
u8 IIC_Read_a_Byte()
{
	u8 i,receive;
	for(i = 0; i < 8; i++)
	{
		receive <<= 1;
		IIC_SCL = 0;
		delay_us(2);
		IIC_SCL = 1;
		delay_us(2);
		receive = receive|(READ_SDA|0x01);
	}
	IIC_SCL = 0;
	IIC_SDA = 0;
	return receive;
}
