#include "SysTick.h"

static u32 fac_us=0;

void SysTick_Init(u8 SYSCLK)
{
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
    fac_us=SYSCLK;
}

void delay_us(u32 nus)
{
    u32 ticks; //½ÚÅÄÊý
    u32 told,tnow,tcnt=0; //
    u32 reload=SysTick->VAL;
    told=SysTick->VAL;
    ticks=nus*fac_us;
    while(1)
    {
        tnow=SysTick->VAL;
        if(told!=tnow)
        {
            if(told>tnow)tcnt+=told-tnow;
            else tcnt+=reload-tnow+told;
            told=tnow;
            if(tcnt>=ticks)break;
        }
    }
}

void delay_ms(u16 nms)
{
    while(nms--)
    {
        delay_us(1000);
    }
}
