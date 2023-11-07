#include "beep.h"
#include "SysTick.h"

void BEEP_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	
	BEEP_PROT_RCC_ENABLE;//ʹ��LED1 GPIO�˿�ʱ��
	
	GPIO_InitStructure.Pin=BEEP_GPIO_PIN; //PF8
    GPIO_InitStructure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
    GPIO_InitStructure.Pull=GPIO_PULLUP;          //����
    GPIO_InitStructure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(BEEP_PROT,&GPIO_InitStructure);
    HAL_GPIO_WritePin(BEEP_PROT,BEEP_GPIO_PIN,GPIO_PIN_RESET);	//PF10��1��Ĭ�ϳ�ʼ�������
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
