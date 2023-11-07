#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "usart.h"
#include "iwdg.h"
#include "key.h"

int fputc(int ch,FILE *f)
{
    while((USART1->SR&0X40)==0);
    USART1->DR=ch;        
    return ch;
}

int main(void)
{
    HAL_Init();                     //初始化HAL库 
	SystemClock_Init(8,336,2,7);   //设置时钟,168Mhz
    SysTick_Init(168);
    LED_Init();
    KEY_Init();
    UART1_Init(115200);
    IWDG_Init(IWDG_PRESCALER_64,6250);
    printf("----------------------------------------------------\r\n");
    LED2=1;
    printf("复位系统\r\n");
    int date=10;
    float fdate=-12.30;
    char string[]="欢迎来到学习爱我，我爱学习实验";
    u16 len=0;
    u16 i=0;
	while(1)
	{   
        if(KEY_Scan(0)==KEY_UP_PRESS)
        {
            printf("-------------------- --------------------------------\r\n");
            IWDG_FeedDog();
            LED2=0;
            printf("喂狗\r\n");
        }
        if(USART1_RX_STA&0X8000)
        {
            len=USART1_RX_STA&0X3FFF;
            HAL_UART_Transmit(&UART1_Handler,(uint8_t*)USART1_RX_BUF,len,5000);
            while(__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_TC)!=SET);           
            USART1_RX_STA=0;
        }
        i++;
        if(i%100==0)
        {                        
            printf("%s\r\n",string);
            LED1=!LED1;
            LED1==0?printf("LED1状态:打开\r\n"):printf("LED1状态:关闭\r\n");
            printf("数字%d\r\n十进制数:%d\r\n八进制数:%o\r\n十六进制数:0X%X\r\n",date,date,date,date);
            printf("当前温度：%2.2fC\r\n",fdate);
            printf("----------------------------------------------------\r\n");
        }            
        delay_ms(10);    
	}
}
