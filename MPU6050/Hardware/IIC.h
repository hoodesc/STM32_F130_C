#ifndef __IIC_H__
#define __IIC_H__

#define FALSE 0
#define TRUE  1

extern void IIC_Init(void);
extern u8 IIC_Start(void);
extern void IIC_Stop(void);
extern void IIC_Ack(void);
extern void IIC_NoAck(void);
extern u8 IIC_Wait_Ack(void);
extern void IIC_Send_a_Byte(u8 dat);
extern u8 IIC_Read_a_Byte(void);


#endif
