#include "system.h"
#include "led.h"

int main(void)
{
    HAL_Init();                     //��ʼ��HAL�� 
	SystemClock_Init(8,336,2,7);   //����ʱ��,168Mhz
	LED_Init();	
	while(1)
	{
		HAL_GPIO_WritePin(LED1_PROT,LED1_GPIO_PIN,GPIO_PIN_RESET);//����PF9�����
        HAL_GPIO_WritePin(LED2_PROT,LED2_GPIO_PIN,GPIO_PIN_RESET);//����PF9�����
	}
}
