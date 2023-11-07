#include "system.h"
#include "beep.h"
#include "SysTick.h"
#include "key.h"
#include "led.h"

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
	LED_Init();
    KEY_Int();
    u8 key=0;
	while(1)
	{
//		if(KEY_Scan(KEY_DISCONTINUOUS)==KEY_UP_PRESS)
//		{
//			LED1=!LED1;
//            delay_ms(200);
//		}
        key=KEY_Scan(KEY_DISCONTINUOUS);
        switch(key)
        {
            case KEY_UP_PRESS: LED1=!LED1;break;
            case KEY0_PRESS: BEEP_Ring();break;         
            case KEY1_PRESS: LED2=!LED2;break;
            case KEY2_PRESS: BEEP_Init();
                             LED_Init();
                             break;
        }
	}
}
