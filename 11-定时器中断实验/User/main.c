#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "time.h"

int main(void)
{
    HAL_Init();                     //��ʼ��HAL�� 
	SystemClock_Init(8,336,2,7);   //����ʱ��,168Mhz
    SysTick_Init(168);
    LED_Init();
    TIM3_Init(5000-1,8400-1);     
	while(1)
	{

	}
}
