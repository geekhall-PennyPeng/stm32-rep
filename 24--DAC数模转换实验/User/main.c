#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "beep.h"
#include "usart.h"
#include "dac.h"
#include "vol.h"
#include "key.h"

int fputc(int ch,FILE *f)
{
    while((USART1->SR&0X40)==0);
    USART1->DR=ch;        
    return ch;
}

int main(void)
{
    u8 i=0;
    u8 key;
    u32 dac_value=0;
    u32 adc_value=0;
    float dac_vol;
    float adc_vol;
    int dacval=0;
    HAL_Init();                     //初始化HAL库 
	SystemClock_Init(8,336,2,7);   //设置时钟,168Mhz
    SysTick_Init(168);
    LED_Init();
    UART1_Init(115200); 
    DAC1_Init();
    Vol_Init();
    KEY_Init();
   
    printf("内部温度实验\r\n");
    
    
	while(1)
	{    
        key=KEY_Scan(KEY_DISCONTINUOUS);
        if(key==KEY_UP_PRESS)
        {
            dacval+=330;
            if(dacval>3300) dacval=3300;
            Set_DAC_Vol(dacval);
        }
        else if(key==KEY0_PRESS)
        {
            dacval-=330;
            if(dacval<=0) dacval=0;
            Set_DAC_Vol(dacval);
        }
        
        i++;
        if(i%20==0)
        {
            LED1=!LED1;
        }
        delay_ms(20);
        if(i%50==0)
        {
            dac_value=Get_DAC_Value();
            dac_vol=(float)dac_value*(3.3/4096);
            adc_value=Get_Vol_Adc_Value();
            adc_vol=(float)adc_value*(3.3/4096);
            printf("设置DAC模拟值为：%d,电压为:%.2f\r\n",dac_value,dac_vol);
            printf("测量ADC模拟值为：%d,电压为:%.2f\r\n",adc_value,adc_vol);
        }
	}
}
