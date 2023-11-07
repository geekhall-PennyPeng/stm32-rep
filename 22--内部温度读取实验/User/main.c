#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "beep.h"
#include "usart.h"
#include "adc.h"
#include "adc_temp.h"

int fputc(int ch,FILE *f)
{
    while((USART1->SR&0X40)==0);
    USART1->DR=ch;        
    return ch;
}

int main(void)
{
    u8 i=0;
    char flag=' ';
    int temp_value=0;
    HAL_Init();                     //��ʼ��HAL�� 
	SystemClock_Init(8,336,2,7);   //����ʱ��,168Mhz
    SysTick_Init(168);
    LED_Init();
    UART1_Init(115200); 
    ADCx_Init();
    printf("�ڲ��¶�ʵ��\r\n");
    
    
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
            temp_value=Get_Temperature_Value();
            if(temp_value>0) flag='+';
            else if(temp_value==0) flag=' ';
            else flag='-';
                      
            printf("����ڲ��¶�Ϊ:%c%.2f��C\r\n",flag,(float)temp_value/100);
            
        }
	}
}
