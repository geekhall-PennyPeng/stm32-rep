#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "time.h"
#include "pwm.h"

int main(void)
{
    HAL_Init();                     //初始化HAL库 
	SystemClock_Init(8,336,2,7);   //设置时钟,168Mhz
    SysTick_Init(168);
    LED_Init();
    TIM14_CH1_PWM_Init(500-1,84-1);//2KMHZ
    u32 compare=0;
    u8 flag=0;
	while(1)
	{
        if(flag==0)
        {
            compare++; 
            if(compare==300)
                flag=1;
        }
        else if(flag==1)
        {
            compare--; 
            if(compare==0)
                flag=0;     
        }
        TIM14_SetCompare1(compare);
        delay_ms(10);    
	}
}
