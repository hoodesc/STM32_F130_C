#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"

//#define SDA_IN() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=8<<12;}
//#define SDA_OUT() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=3<<12;}
//#define SDA_IN() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=8<<12;}
//#define SDA_OUT() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=3<<12;}

#define IIC_SCL PBout(0)
#define IIC_SDA PBout(1)
#define READ_SDA PBin(1)

void IIC_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;	//	推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

void SDA_IN()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//	上拉输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

void SDA_OUT()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//	推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

/*	IIC起始信号		*/
void IIC_Start()
{
	SDA_OUT();
	IIC_SDA=1;
	IIC_SCL=1;
	delay_us(2);
	IIC_SDA=0;
	delay_us(2);
	IIC_SCL=0;
	delay_us(2);
}

void IIC_Send_Byte(u8 dat)
{
	u8 i;
	SDA_OUT();
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

u8 IIC_Read_Byte()
{
	u8 i,receive;
	SDA_IN();
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

/*	IIC停止信号	*/
void IIC_Stop()
{
	SDA_OUT();
	IIC_SDA=0;
	IIC_SCL=1;
	delay_us(2);
	IIC_SDA=1;
	delay_us(2);
}

void IIC_Ack()
{
	SDA_OUT();
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
	SDA_OUT();
	IIC_SDA=1;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}

u8 IIC_Wait_Ack()
{
	u8 delaytime;
	SDA_IN();
	IIC_SDA = 1;
	IIC_SCL = 1;
	delay_us(2);
	while(READ_SDA)
	{
		delaytime++;
		if(delaytime > 250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL = 0;
	delay_us(2);	
	return 0;
}
int main()
{
	u8 dat = 0;
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//	设置NVIC中断分钟2:  2位抢占优先级，2位响应优先级
	IIC_Init();
	delay_init();
	while(1)
	{
		delay_ms(20);
//		IIC_Start();
//		IIC_Send_Byte(0xA0);	
//		IIC_Wait_Ack();
//		IIC_Send_Byte(0xB0);	
//		IIC_Wait_Ack();
//		IIC_Send_Byte(0x2F);
//		IIC_Wait_Ack();
//		IIC_Stop();	
		
		IIC_Start();
		IIC_Send_Byte(0xD0);
		IIC_Wait_Ack();
		IIC_Send_Byte(0xB0);
		IIC_Wait_Ack();
		IIC_Start();
		IIC_Send_Byte(0xA0 | 0x01);
		IIC_Wait_Ack();
		dat = IIC_Read_Byte();
		IIC_Ack();
		IIC_Stop();
		
//		IIC_Send_Byte(0x11);	
//		IIC_Wait_Ack();			
		delay_ms(20);
	}
}

