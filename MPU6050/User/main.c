#include "stm32f10x.h"
#include "delay.h"
#include "MPU6050.h"


u8 BUF[2];	

u8 IIC_Write_a_Byte_to_reg(u8 reg1,u8 reg2,u8 dat)
{
	if(IIC_Start())
	{
		IIC_Send_a_Byte(reg1);
		if(!IIC_Wait_Ack()) return FALSE;
		IIC_Send_a_Byte(reg2);
		if(!IIC_Wait_Ack()) return FALSE;
		IIC_Send_a_Byte(dat);
		if(!IIC_Wait_Ack()) return FALSE;
		IIC_Stop();
		delay_ms(2);
		return TRUE;
	}
	else
		return FALSE;

}

u8 IIC_Read_a_Byte_for_reg(u8 SlaveAddress,u8 reg)
{
	u8 REG_data;
	if(!IIC_Start())	return FALSE;
	IIC_Send_a_Byte(SlaveAddress);
	if(!IIC_Wait_Ack()) return FALSE;
	IIC_Send_a_Byte(reg);
	IIC_Wait_Ack();
  IIC_Start();	
	IIC_Send_a_Byte(SlaveAddress|0x01);	
	IIC_Wait_Ack();
	REG_data = IIC_Read_a_Byte();
	IIC_NoAck();
	IIC_Stop();
	return REG_data;
	
}
void MPU6050_Init()
{
		IIC_Write_a_Byte_to_reg(MPU6050_Addr,PWR_MGMT_1,0x00);		//解除休眠
		IIC_Write_a_Byte_to_reg(MPU6050_Addr,SMPLRT_DIV,0x07);		//陀螺仪采样率
		IIC_Write_a_Byte_to_reg(MPU6050_Addr,CONFIG,0x06);				//低通滤波频率
		IIC_Write_a_Byte_to_reg(MPU6050_Addr,GYRO_CONFIG,0x18);		//陀螺仪自检及测量范围
		IIC_Write_a_Byte_to_reg(MPU6050_Addr,ACCEL_CONFIG,0x01);	//加速计自检、测量范围及高通滤波频率
}

void Read_MPU6050()
{
	BUF[0] = IIC_Read_a_Byte_for_reg(MPU6050_Addr,TEMP_OUT_L);
	BUF[1] = IIC_Read_a_Byte_for_reg(MPU6050_Addr,TEMP_OUT_H);	
}

int main()
{
	IIC_Init();
	delay_init();
	delay_ms(10);
	MPU6050_Init();
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//	设置NVIC中断分钟2:  2位抢占优先级，2位响应优先级
	while(1)
	{
		Read_MPU6050();
		delay_ms(2);
	}
}

