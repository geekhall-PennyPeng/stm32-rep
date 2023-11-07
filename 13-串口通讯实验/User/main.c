#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "usart.h"


int main(void)
{
    HAL_Init();                     //初始化HAL库 
	SystemClock_Init(8,336,2,7);   //设置时钟,168Mhz
    SysTick_Init(168);
    LED_Init();
    UART1_Init(115200);
    u16 len=0;
    u16 i=0;
	while(1)
	{   
        if(USART1_RX_STA&0X8000)
        {
            len=USART1_RX_STA&0X3FFF;
            HAL_UART_Transmit(&UART1_Handler,(uint8_t*)USART1_RX_BUF,len,5000);
            while(__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_TC)!=SET);           
            USART1_RX_STA=0;
        }
        i++;
        if(i%20==0)
            LED1=!LED1;
        delay_ms(10);    
	}
}
