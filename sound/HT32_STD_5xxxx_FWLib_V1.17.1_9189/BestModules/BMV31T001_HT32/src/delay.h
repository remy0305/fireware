#ifndef ___DELAY_H__
#define ___DELAY_H__

#include "ht32.h"

extern u32 Systick_count;

extern void SYSTICK_Config(void);
extern void  delay_us(u32 nus);
extern void  delay_ms(u32 nms);
void delay_MS(unsigned long ms);
u32 Get_Sys_ms(void);
u32 Get_Sys_us(void);




#endif
