#include "system.h"
#include "led.h"
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
	LED_Init();	
    LED2=0;
	while(1)
	{
		LED1=!LED1;  //D1状态取反
        LED2=!LED2;  //D1状态取反
        delay_ms(1000);
	}
}
