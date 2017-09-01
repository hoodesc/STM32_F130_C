#include "stm32f10x.h"
#include "exit.h"
#include "led.h"


void EXTIT_Init(void)
{
	EXTI_InitTypeDef EXTI_InitSture;
	NVIC_InitTypeDef NVIC_InitStrue;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//使能复用功能时钟	
	EXTI_InitSture.EXTI_Line = EXTI_Line0;//选中中断线0
	EXTI_InitSture.EXTI_LineCmd = ENABLE;
	EXTI_InitSture.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitSture.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
	EXTI_Init(&EXTI_InitSture);//初始化外部中断
	
	NVIC_InitStrue.NVIC_IRQChannel = EXTI0_IRQn;//使能外部中断通道0
	NVIC_InitStrue.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority = 1;//抢占优先级1
	NVIC_InitStrue.NVIC_IRQChannelSubPriority = 1;//响应优先级1
	NVIC_Init(&NVIC_InitStrue);
}

//外部中断0服务函数
void EXTI0_IRQHandler(void)
{
	LED = ~LED;
	EXTI_ClearITPendingBit(EXTI_Line0);
}



