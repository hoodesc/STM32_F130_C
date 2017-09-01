#include "stm32f10x.h"
#include "sys.h"
#include "led.h"
#include "key.h"
#include "exti.h"

void IWDG_Init(uint8_t prer,uint16_t rlr)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);	//ȡ���Ĵ���д����
	IWDG_SetPrescaler(prer);	//����IWDGԤ��Ƶϵ��
	IWDG_SetReload(rlr);		//����IWDG��װ��ֵ
	IWDG_ReloadCounter();	//��װ�ؼ���ֵ
	IWDG_Enable();	//����IWDG
}

int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	LED_Init();
	EXTI0_Init();
	KEY_Init();
	IWDG_Init(4,625);
	while(1)
	{

	}
}

