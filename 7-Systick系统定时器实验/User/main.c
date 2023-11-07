#include "system.h"
#include "led.h"
#include "SysTick.h"

void delay(u32 i)
{
    while(i--);
}

int main(void)
{
    HAL_Init();                     //��ʼ��HAL�� 
	SystemClock_Init(8,336,2,7);   //����ʱ��,168Mhz
    SysTick_Init(168);
	LED_Init();	
    LED2=0;
	while(1)
	{
		LED1=!LED1;  //D1״̬ȡ��
        LED2=!LED2;  //D1״̬ȡ��
        delay_ms(1000);
	}
}
