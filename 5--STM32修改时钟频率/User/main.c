#include "system.h"
#include "led.h"

void delay(u32 i)
{
    while(i--);
}

int main(void)
{
    HAL_Init();                     //初始化HAL库 
	SystemClock_Init(8,336,8,7);   //设置时钟,168Mhz
	LED_Init();	
	while(1)
	{
		HAL_GPIO_WritePin(LED1_PROT,LED1_GPIO_PIN,GPIO_PIN_RESET);//设置PF9输出低
        HAL_GPIO_WritePin(LED1_PROT,LED2_GPIO_PIN,GPIO_PIN_SET);//设置PF10输出高
        delay(6000000);
        HAL_GPIO_WritePin(LED2_PROT,LED2_GPIO_PIN,GPIO_PIN_RESET);//设置PF9输出低
        HAL_GPIO_WritePin(LED2_PROT,LED1_GPIO_PIN,GPIO_PIN_SET);//设置PF10输出低
        delay(6000000);
	}
}
