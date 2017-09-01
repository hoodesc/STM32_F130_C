#include "stm32f10x.h"
#include "sys.h"
#include "led.h"
#include "exit.h"
#include "key.h"


int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	LED_Init();
	KEY_Init();
	EXTIT_Init();
	while(1)
	{

	}
}

