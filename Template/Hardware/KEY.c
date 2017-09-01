#include "stm32f10x.h"
#include "key.h"


void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitSture;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能GPIOA时钟
	GPIO_InitSture.GPIO_Mode = GPIO_Mode_IPU;//输入上拉
	GPIO_InitSture.GPIO_Pin = GPIO_Pin_0;//选中GPIO0
	GPIO_InitSture.GPIO_Speed = GPIO_Speed_50MHz;//速度
	GPIO_Init(GPIOA,&GPIO_InitSture);//初始化GPIOA.13
}

