#include "system.h"
#include "led.h"

int main(void)
{
    HAL_Init();                     //初始化HAL库 
	SystemClock_Init(8,336,2,7);   //设置时钟,168Mhz
	LED_Init();	
	while(1)
	{
		HAL_GPIO_WritePin(LED1_PROT,LED1_GPIO_PIN,GPIO_PIN_RESET);//设置PF9输出低
        HAL_GPIO_WritePin(LED2_PROT,LED2_GPIO_PIN,GPIO_PIN_RESET);//设置PF9输出低
	}
}
