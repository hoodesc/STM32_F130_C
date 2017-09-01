#ifndef __LED_H__
#define __LED_H__
#include "sys.h"
extern void LED_Init(void);

#define LED PCout(13)
#endif
