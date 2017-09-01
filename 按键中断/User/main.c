#include "stm32f10x.h"
#include "sys.h"


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

void Key_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	//	使能GPIOA时钟
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		//	输入上拉
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				//	选中GPIO0
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}

void EXIT_Init()
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
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;	//	选中外部中断通道0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		//	使能外部中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//	抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;	//	子优先级2
	NVIC_Init(&NVIC_InitStructure);
}

void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0)!=RESET)
	{
		LED = ~LED;	
		EXTI_ClearITPendingBit(EXTI_Line0); //	清除中断线0标志
	}
	
}
int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//	设置NVIC中断分钟2:  2位抢占优先级，2位响应优先级
	LED_Init();
	Key_Init();
	EXIT_Init();
	while(1)
	{
	}
}

