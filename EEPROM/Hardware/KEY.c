#include "stm32f10x.h"
#include "key.h"


//	KEY S2初始化，低电平按下
void KEY_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	//	使能GPIOA时钟
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;			//	输入上拉
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				//	选中GPIO0
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}
