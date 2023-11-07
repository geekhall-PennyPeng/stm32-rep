#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "beep.h"
#include "usart.h"
#include "key.h"
#include "touch_key.h"



int fputc(int ch,FILE *f)
{
    while((USART1->SR&0X40)==0);
    USART1->DR=ch;        
    return ch;
}

int main(void)
{
    u8 i=0;
    HAL_Init();                     //初始化HAL库 
	SystemClock_Init(8,336,2,7);   //设置时钟,168Mhz
    SysTick_Init(168);
    LED_Init();
    BEEP_Init();
    UART1_Init(115200); 
    printf("触摸按键捕获实验");
    Touch_Key_Init(4);    
    
	while(1)
	{   
        if(Touch_Key_Scan(0))
        {
           LED2=!LED2; 
           BEEP_Ring();
        }
        i++;
        if(i%20==0)
        {
            LED1=!LED1;
        }
        delay_ms(10);
	}
}
