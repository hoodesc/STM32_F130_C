#include "stm32f10x.h"
#include "sys.h"
#include "led.h"
#include "key.h"
#include "exti.h"

void IWDG_Init(uint8_t prer,uint16_t rlr)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);	//取消寄存器写保护
	IWDG_SetPrescaler(prer);	//设置IWDG预分频系数
	IWDG_SetReload(rlr);		//设置IWDG重装载值
	IWDG_ReloadCounter();	//重装载计数值
	IWDG_Enable();	//启动IWDG
}

int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	LED_Init();
	EXTI0_Init();
	KEY_Init();
	IWDG_Init(4,625);
	while(1)
	{

	}
}

