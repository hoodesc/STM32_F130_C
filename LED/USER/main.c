#include "stm32f10x.h"
#define LED_L GPIO_SetBits(GPIOC,GPIO_Pin_13)
#define LED_H GPIO_ResetBits(GPIOC,GPIO_Pin_13)

void delay_ms(long time)
{
	long i = 0;
	while(time--)
	{
		i = 12000;
		while(i--);
	}
}


//	LED D2初始化,高电平点亮
void LED_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	GPIO_SetBits(GPIOC,GPIO_Pin_13);	//	熄灭
}
int main()
{
	LED_Init();
	while(1)
	{
		LED_H;
		delay_ms(200);
		LED_L;
		delay_ms(200);
	}
}

