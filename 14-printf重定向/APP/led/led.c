#include "led.h"


/*******************************************************************************
* 函 数 名         : LED_Init
* 函数功能		   : LED初始化函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	LED1_PROT_RCC_ENABLE;//使能LED1 GPIO端口时钟
    LED2_PROT_RCC_ENABLE;//使能LED2 GPIO端口时钟
	
	GPIO_InitStructure.Pin=LED1_GPIO_PIN; //PF9,10 
    GPIO_InitStructure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
    GPIO_InitStructure.Pull=GPIO_PULLUP;          //上拉
    GPIO_InitStructure.Speed=GPIO_SPEED_HIGH;     //高速
    HAL_GPIO_Init(LED1_PROT,&GPIO_InitStructure);
    
    GPIO_InitStructure.Pin=LED2_GPIO_PIN; //PF9,10 
    GPIO_InitStructure.Speed=GPIO_SPEED_HIGH;     //高速
    HAL_GPIO_Init(LED2_PROT,&GPIO_InitStructure);
	
	HAL_GPIO_WritePin(LED1_PROT,LED1_GPIO_PIN,GPIO_PIN_SET);	//PF9置1，默认初始化后灯灭
    HAL_GPIO_WritePin(LED2_PROT,LED2_GPIO_PIN,GPIO_PIN_SET);	//PF10置1，默认初始化后灯灭
}
