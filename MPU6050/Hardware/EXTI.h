#ifndef __exti_h__
#define __exti_h__
#include "stm32f10x.h"

void EXTI0_Init()
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);		//ʹ��AFIOʱ��
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);	//	����GPIOA.0���ж���0
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;	//	ѡ���ж���0
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		//	�ж�
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//	�½��ش���
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;	//ѡ���ⲿ�ж�ͨ��0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		//ʹ���ⲿ�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;	//�����ȼ�2
	NVIC_Init(&NVIC_InitStructure);
}

void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0)!=RESET)
	{
		IWDG_ReloadCounter();
		EXTI_ClearITPendingBit(EXTI_Line0); //����ж���0��־
	}
	
}

#endif
