//	LED D2��ʼ��,�ߵ�ƽ����
void LED_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	GPIO_SetBits(GPIOC,GPIO_Pin_13);	//	Ϩ��
}
//	KEY S2��ʼ�����͵�ƽ����
void Key_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	//	ʹ��GPIOAʱ��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;			//	��������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				//	ѡ��GPIO0
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}