#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "usart.h"
#include "key.h"
#include "input.h"


int fputc(int ch,FILE *f)
{
    while((USART1->SR&0X40)==0);
    USART1->DR=ch;        
    return ch;
}

int main(void)
{
    u8 i=0;
    long long indata=0;
    HAL_Init();                     //初始化HAL库 
	SystemClock_Init(8,336,2,7);   //设置时钟,168Mhz
    SysTick_Init(168);
    LED_Init();
    UART1_Init(115200);   
    TIM5_CH1_Input_Init(0XFFFFFFFF-1,84-1);
    printf("输入捕获实验\n");
	while(1)
	{         
        if(TIM5_CH1_CAPTURE_STA&0x80)
        {
            indata=TIM5_CH1_CAPTURE_STA&0X3F;
            indata*=0XFFFFFFFF;
            indata+=TIM5_CH1_CAPTURE_VAL;
            printf("高电平持续时间：%lld us\n",indata);
            TIM5_CH1_CAPTURE_STA=0;
        }
        i++;
        if(i%20==0)
        {
            LED1=!LED1;
        }
        delay_ms(10);
	}
}
