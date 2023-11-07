#include "beep.h"
#include "SysTick.h"

void BEEP_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	
	BEEP_PROT_RCC_ENABLE;//使能LED1 GPIO端口时钟
	
	GPIO_InitStructure.Pin=BEEP_GPIO_PIN; //PF8
    GPIO_InitStructure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
    GPIO_InitStructure.Pull=GPIO_PULLUP;          //上拉
    GPIO_InitStructure.Speed=GPIO_SPEED_HIGH;     //高速
    HAL_GPIO_Init(BEEP_PROT,&GPIO_InitStructure);
    HAL_GPIO_WritePin(BEEP_PROT,BEEP_GPIO_PIN,GPIO_PIN_RESET);	//PF10置1，默认初始化后灯灭
}

void BEEP_Ring(void)
{
	BEEP=!BEEP;
}

/*
void BEEP_Select(u16 mode)
{
    switch(mode)
    {
        case 1:BEEP_Mode1();
    }
}

void BEEP_Mode1(void)
{
    
}
*/
