#ifndef __exti_h__
#define __exti_h__
#include "stm32f10x.h"

void EXTI0_Init()
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);		//使能AFIO时钟
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);	//	连接GPIOA.0与中断线0
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;	//	选中中断线0
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		//	中断
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//	下降沿触发
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;	//选中外部中断通道0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		//使能外部中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;	//子优先级2
	NVIC_Init(&NVIC_InitStructure);
}

void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0)!=RESET)
	{
		IWDG_ReloadCounter();
		EXTI_ClearITPendingBit(EXTI_Line0); //清除中断线0标志
	}
	
}

#endif
