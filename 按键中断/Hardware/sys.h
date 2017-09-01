#ifndef __SYS_H
#define __SYS_H	
#include "stm32f10x.h"
#define LED GPIOC_ODR->bit13
typedef struct 
{ 
u8 bit0:1; 
u8 bit1:1; 
u8 bit2:1; 
u8 bit3:1; 
u8 bit4:1; 
u8 bit5:1; 
u8 bit6:1; 
u8 bit7:1; 

u8 bit8:1; 
u8 bit9:1; 
u8 bit10:1; 
u8 bit11:1; 
u8 bit12:1; 
u8 bit13:1; 
u8 bit14:1; 
u8 bit15:1; 

}FLAG_16BIT_TypeDef; 
//IO偏移地址
#define GPIOA_ODR              	((__IO FLAG_16BIT_TypeDef*)(GPIOA_BASE+12)) 
#define GPIOB_ODR               	((__IO FLAG_16BIT_TypeDef*)(GPIOB_BASE+12)) 
#define GPIOC_ODR               	((__IO FLAG_16BIT_TypeDef*)(GPIOC_BASE+12)) 
#define GPIOD_ODR               	((__IO FLAG_16BIT_TypeDef*)(GPIOD_BASE+12)) 
#define GPIOF_ODR              	((__IO FLAG_16BIT_TypeDef*)(GPIOF_BASE+12)) 
#endif
