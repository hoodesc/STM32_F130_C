#include "stm32f10x.h"
#include "sys.h"
#include "led.h"
#include "exit.h"
#include "key.h"


int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	LED_Init();
	KEY_Init();
	EXTIT_Init();
	while(1)
	{

	}
}

