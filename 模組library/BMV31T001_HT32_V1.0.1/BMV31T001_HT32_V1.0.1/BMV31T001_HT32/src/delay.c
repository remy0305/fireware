#include "delay.h"

 u32 Systick_count;


static const u32 ReloadValue=60000000/1000;


u32 Get_Sys_ms(void)
{
	return  Systick_count;
}

u32 Get_Sys_us(void)
{
	return  Systick_count*1000+(ReloadValue-SysTick->VAL)/(ReloadValue/1000);
}


void SysTick_Handler(void)//1ms
{
	Systick_count++;
}

void  delay_us(u32 nus)
{
//	u32 couter;
//	couter = Get_Sys_us();
//	while(Get_Sys_us() - couter < nus);

	HT_BFTM0->SR=0;
	HT_BFTM0->CMP = nus*60;
	HT_BFTM0->CR |= 3<<1;  //SINGLE //ENABLE
	while(HT_BFTM0->SR==0);
}

		
void  delay_ms(u32 nms)
{
	u32 i;	
  for(i=0;i<nms;i++)
	{
		delay_us(1000);
	}
}
u8 rand_0_1(void)
{
	return SysTick->VAL&0x00000001;//
}


u8 rand_0_3(void)
{
	return SysTick->VAL&0x00000003;//
}


u8 rand_0_7(void)
{
	return SysTick->VAL&0x00000007;//
}

u8 rand_0_15(void)
{
	return SysTick->VAL&0x0000000f;//
}


u8 rand_0_31(void)
{
	return SysTick->VAL&0x0000001f;//
}

u8 rand_0_63(void)
{
	return SysTick->VAL&0x0000003f;//
}

u8 rand_0_127(void)
{
	return SysTick->VAL&0x0000007f;//
}

void delay_MS(unsigned long ms)
{
	unsigned long i,j;
	
	for(i=0;i<ms;i++)
	{
		for(j=0;j<10000;j++)
		{
			__NOP();
		}
	}
}

