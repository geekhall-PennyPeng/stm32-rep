#include "system.h"
#include "beep.h"
#include "SysTick.h"
#include "key.h"
#include "led.h"
#include "exti.h"

int main(void)
{
    HAL_Init();                     //��ʼ��HAL�� 
	SystemClock_Init(8,336,2,7);   //����ʱ��,168Mhz
    SysTick_Init(168);
    EXTI_Init();
	BEEP_Init();
	LED_Init();
	while(1)
	{

	}
}
