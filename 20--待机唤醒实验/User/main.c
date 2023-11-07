#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "beep.h"
#include "usart.h"
#include "wkup.h"

int fputc(int ch,FILE *f)
{
    while((USART1->SR&0X40)==0);
    USART1->DR=ch;        
    return ch;
}

int main(void)
{
    int i;
    HAL_Init();                     //初始化HAL库 
	SystemClock_Init(8,336,2,7);   //设置时钟,168Mhz
    SysTick_Init(168);
    LED_Init();
    BEEP_Init();
    UART1_Init(115200); 
   
    printf("待机唤醒实验\r\n");
    
    
	while(1)
	{           
        for(i=5;i>0;i--)
        {
            printf("待机倒计时:%d\r\n",i);
            delay_ms(1000);
            LED1=!LED1;
        }
        printf("Standby.............\r\n");
        Enter_Standby_Mode();
        
	}
}
