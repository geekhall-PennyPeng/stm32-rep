#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "beep.h"
#include "usart.h"
#include "adc.h"
#include "adc_temp.h"
#include "lsens.h"

int fputc(int ch,FILE *f)
{
    while((USART1->SR&0X40)==0);
    USART1->DR=ch;        
    return ch;
}

int main(void)
{
    u8 i=0;
    int temp_value=0;
    u8 light_value=0;
    HAL_Init();                     //初始化HAL库 
	SystemClock_Init(8,336,2,7);   //设置时钟,168Mhz
    SysTick_Init(168);
    LED_Init();
    UART1_Init(115200); 
    Lsens_Init();
    Temp_Init();
    printf("内部温度实验\r\n");
    
    
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
            light_value=Lsens_Get_Value();
            temp_value=Get_Temperature_Value();
            printf("检测光照强度为:%d\r\n",light_value);          
            printf("检测内部温度为:%.2f°C\r\n",(float)(temp_value/100));
            
        }
	}
}
