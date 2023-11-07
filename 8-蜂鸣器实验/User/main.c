#include "system.h"
#include "beep.h"
#include "SysTick.h"

void delay(u32 i)
{
    while(i--);
}

int main(void)
{
    HAL_Init();                     //初始化HAL库 
	SystemClock_Init(8,336,2,7);   //设置时钟,168Mhz
    SysTick_Init(168);
	BEEP_Init();	
	while(1)
	{
		BEEP=!BEEP;
        delay_ms(250);
	}
}
