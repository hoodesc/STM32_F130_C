#include "stm32f10x.h"
#include "key.h"


void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitSture;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��GPIOAʱ��
	GPIO_InitSture.GPIO_Mode = GPIO_Mode_IPU;//��������
	GPIO_InitSture.GPIO_Pin = GPIO_Pin_0;//ѡ��GPIO0
	GPIO_InitSture.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�
	GPIO_Init(GPIOA,&GPIO_InitSture);//��ʼ��GPIOA.13
}

