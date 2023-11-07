#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "beep.h"
#include "usart.h"
#include "rng.h"

int fputc(int ch,FILE *f)
{
    while((USART1->SR&0X40)==0);
    USART1->DR=ch;        
    return ch;
}

int main(void)
{
    u8 i=0;
    int random=0;
    HAL_Init();                     //初始化HAL库 
	SystemClock_Init(8,336,2,7);   //设置时钟,168Mhz
    SysTick_Init(168);
    LED_Init();
    BEEP_Init();
    UART1_Init(115200);     
    printf("随机数生成实验\r\n"); 
    while(RNG_Init())
    {
        printf("RNG Error\r\n");
    }
    
	while(1)
	{           
        i++;
        if(i%20==0)
        {
            random=RNG_Get_RandomRange(0,100);
            printf("随机数为:%d\r\n",random);
            LED1=!LED1;
        }
        delay_ms(10);
	}
}
