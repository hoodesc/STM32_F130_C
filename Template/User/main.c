#include "stm32f10x.h"
#include "sys.h"


void SPI2_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_INitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);		//PortB时钟使能
	RCC_APB1PeriphClockCmd(RCC_APB1ENR_SPI2EN,ENABLE);			//SPI2时钟使能
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;					//复用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
	
	SPI_INitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
	SPI_INitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_INitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_INitStructure.SPI_CRCPolynomial = 7;
	SPI_INitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_INitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_INitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_INitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_INitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_Init(SPI2,&SPI_INitStructure);
	SPI_Cmd(SPI2,ENABLE);
}

u8 SPI2_ReadWriteByte(u8 dat)
{
	u8 i = 0;
	while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE) == RESET)		//等待发送区为空
	{
		i++;
		if(i > 200)	return 0;
	}
	SPI_I2S_SendData(SPI2,dat);
	i = 0;
	while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_RXNE) == RESET)		//等待接收
	{
		i++;
		if(i > 200)	return 0;
	}
	return SPI_I2S_ReceiveData(SPI2);		//返回SPI2数据
}

int main()
{
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//	设置NVIC中断分钟2:  2位抢占优先级，2位响应优先级
	while(1)
	{

	}
}

