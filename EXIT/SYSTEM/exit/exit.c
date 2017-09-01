#include "stm32f10x.h"
#include "exit.h"
#include "led.h"


void EXTIT_Init(void)
{
	EXTI_InitTypeDef EXTI_InitSture;
	NVIC_InitTypeDef NVIC_InitStrue;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//ʹ�ܸ��ù���ʱ��	
	EXTI_InitSture.EXTI_Line = EXTI_Line0;//ѡ���ж���0
	EXTI_InitSture.EXTI_LineCmd = ENABLE;
	EXTI_InitSture.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitSture.EXTI_Trigger = EXTI_Trigger_Falling;//�½��ش���
	EXTI_Init(&EXTI_InitSture);//��ʼ���ⲿ�ж�
	
	NVIC_InitStrue.NVIC_IRQChannel = EXTI0_IRQn;//ʹ���ⲿ�ж�ͨ��0
	NVIC_InitStrue.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority = 1;//��ռ���ȼ�1
	NVIC_InitStrue.NVIC_IRQChannelSubPriority = 1;//��Ӧ���ȼ�1
	NVIC_Init(&NVIC_InitStrue);
}

//�ⲿ�ж�0������
void EXTI0_IRQHandler(void)
{
	LED = ~LED;
	EXTI_ClearITPendingBit(EXTI_Line0);
}



