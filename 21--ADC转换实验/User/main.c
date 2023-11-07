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
    HAL_Init();                     //��ʼ��HAL�� 
	SystemClock_Init(8,336,2,7);   //����ʱ��,168Mhz
    SysTick_Init(168);
    LED_Init();
    UART1_Init(115200); 
    ADCx_Init();
    printf("adcת��ʵ��\r\n");
    
    
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
            printf("���ADֵΪ:%d\r\n",adc_value);
            printf("����ѹֵΪ:%.2f\r\n",vol);
        }
	}
}
