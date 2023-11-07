#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "beep.h"
#include "usart.h"
#include "adc.h"


int fputc(int ch,FILE *f)
{
    while((USART1->SR&0X40)==0);
    USART1->DR=ch;        
    return ch;
}

int main(void)
{
    u8 i=0;
    u16 adc_value=0;
    float vol;
    HAL_Init();                     //初始化HAL库 
	SystemClock_Init(8,336,2,7);   //设置时钟,168Mhz
    SysTick_Init(168);
    LED_Init();
    UART1_Init(115200); 
    ADCx_Init();
    printf("adc转换实验\r\n");
    
    
	while(1)
	{           
       
        i++;
        if(i%20==0)
        {
            LED1=!LED1;
        }
        delay_ms(20);
        if(i%50==0)
        {
            adc_value=Get_ADC_Value(ADC_CHANNEL_5,20);
            vol=adc_value*3.3/4096;
            printf("检测AD值为:%d\r\n",adc_value);
            printf("检测电压值为:%.2f\r\n",vol);
        }
	}
}
