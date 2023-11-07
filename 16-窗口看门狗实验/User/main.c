#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "usart.h"
#include "key.h"
#include "wwdg.h"

int fputc(int ch,FILE *f)
{
    while((USART1->SR&0X40)==0);
    USART1->DR=ch;        
    return ch;
}

int main(void)
{
    HAL_Init();                     //初始化HAL库 
	SystemClock_Init(8,336,2,7);   //设置时钟,168Mhz
    SysTick_Init(168);
    LED_Init();
    UART1_Init(115200);   
    LED1=0;
    delay_ms(500);
    WWDG_Init(0X7F,0X5F,WWDG_PRESCALER_8);
    
	while(1)
	{   
        LED1=1;
	}
}
