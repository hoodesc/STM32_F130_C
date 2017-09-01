#include "stm32f10x.h"
#include "led.h"

void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitSture;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//ʹ��GPIOCʱ��
	GPIO_InitSture.GPIO_Mode = GPIO_Mode_Out_PP;//�������
	GPIO_InitSture.GPIO_Pin = GPIO_Pin_13;//ѡ��GPIO13
	GPIO_InitSture.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�	
	GPIO_Init(GPIOC,&GPIO_InitSture);
}
