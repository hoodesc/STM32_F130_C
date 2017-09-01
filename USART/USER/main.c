#include "stm32f10x.h"

void My_USART_Init()
{
	GPIO_InitTypeDef GPIO_InitStrue;
	USART_InitTypeDef USART_InitStrue;
//	NVIC_InitTypeDef NVIC_InitStrue;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	GPIO_InitStrue.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStrue.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStrue.GPIO_Speed = GPIO_Speed_10MHz;	
	GPIO_Init(GPIOA,&GPIO_InitStrue);

	GPIO_InitStrue.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStrue.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStrue.GPIO_Speed = GPIO_Speed_10MHz;	
	GPIO_Init(GPIOA,&GPIO_InitStrue);	
//USART1初始化
	USART_InitStrue.USART_BaudRate = 115200;
	USART_InitStrue.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStrue.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
	USART_InitStrue.USART_Parity = USART_Parity_No;
	USART_InitStrue.USART_StopBits = USART_StopBits_1;
	USART_InitStrue.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1,&USART_InitStrue);
	
	USART_Cmd(USART1,ENABLE);		//使能USART1

//	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
////中断优先级设置	
//	NVIC_InitStrue.NVIC_IRQChannel = USART1_IRQn;
//	NVIC_InitStrue.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority = 1;
//	NVIC_InitStrue.NVIC_IRQChannelSubPriority = 1;
//	NVIC_Init(&NVIC_InitStrue);	
}

//void USART1_IRQHandler(void)
//{
//	u8 rec;
//	if(USART_GetITStatus(USART1,USART_IT_RXNE))
//	{
//			rec = USART_ReceiveData(USART1);
//			if(rec == 0x80)
//			{
//				USART_SendData(USART1,1);					
//			}
//	}
//}


int main()
{
	u8 temp[] = "1234";
	u8 i = 0;
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	My_USART_Init();


//	while(temp[i] != '\0')
//	{
		USART_SendData(USART1,temp[0]);
//		while(USART_GetFlagStatus(USART1,USART_FLAG_TC) == 0);
//		i++;
//	}
	while(1);
}
